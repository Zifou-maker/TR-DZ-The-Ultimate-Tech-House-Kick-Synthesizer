/* -------------------------------------------------------
   TR-DZ V18.0 - "THE CONDUCTOR" (Séquenceur à Patterns)
   Introduction des rythmes Tech House.
   -------------------------------------------------------
*/

#include "DaisyDuino.h"

using namespace daisysp;

// --- CONFIG ---
const int MUX_S0 = 0, MUX_S1 = 1, MUX_S2 = 2, MUX_S3 = 3;
const int MUX_SIG = A0; 

static DaisyHardware hw;
static Metro         metro;

// --- MOTEUR DSP ---
static Oscillator    osc_kick;
static AdEnv         env_amp_kick;
static AdEnv         env_pitch_kick;
static WhiteNoise    noise_click;
static AdEnv         env_click;
static Svf           filt_click; 
static Oscillator    osc_bass;

// --- SÉQUENCEUR ---
int current_step = 0; // De 0 à 15
int selected_pattern = 0;

// La Bibliothèque de Rythmes (1 = Kick, 0 = Silence)
// 16 pas par pattern
const int NUM_PATTERNS = 5;
bool patterns[NUM_PATTERNS][16] = {
    // 0. Techno Straight (4/4 Classique)
    {1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0},
    
    // 1. Tech House Basic (Avec un petit extra à la fin)
    {1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,1},
    
    // 2. The "Charleston" (Syncopé)
    {1,0,0,1, 0,0,1,0, 1,0,0,0, 1,0,0,0},
    
    // 3. Berlinoise (Minimal)
    {1,0,0,0, 0,0,0,0, 1,0,0,0, 0,0,1,0},
    
    // 4. ROLL (Roulement de fin de mesure)
    {1,0,1,0, 1,0,1,0, 1,1,1,1, 1,1,1,1}
};

// --- VARIABLES ---
float tune_val = 0.5f;
float sidechain_val = 0.0f;
float decay_val = 0.3f;
float click_val = 0.5f;
float drive_val = 0.0f;
float bpm = 126.0f;

float last_values[16] = {0.0f}; 
const float HYSTERESIS = 0.005f;

float SoftClip(float in, float drive) { return tanhf(in * drive); }

float readMux(int channel) {
    digitalWrite(MUX_S0, (channel & 1) ? HIGH : LOW);
    digitalWrite(MUX_S1, (channel & 2) ? HIGH : LOW);
    digitalWrite(MUX_S2, (channel & 4) ? HIGH : LOW);
    digitalWrite(MUX_S3, (channel & 8) ? HIGH : LOW);
    delayMicroseconds(30); 
    float newVal = analogRead(MUX_SIG) / 1023.0f;
    if (abs(newVal - last_values[channel]) > HYSTERESIS) last_values[channel] = newVal;
    return last_values[channel];
}

void AudioCallback(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        
        // Séquenceur avance à chaque Tic
        if (metro.Process()) {
            current_step++;
            if (current_step > 15) current_step = 0;

            // EST-CE QU'ON DOIT JOUER ?
            if (patterns[selected_pattern][current_step] == 1) {
                env_amp_kick.Trigger();
                env_pitch_kick.Trigger();
                env_click.Trigger();
            }
        }

        // --- DSP ENGINE (Identique V17) ---
        float env_p = env_pitch_kick.Process();
        float env_a = env_amp_kick.Process();
        osc_kick.SetFreq(45.0f + (env_p * 220.0f)); 
        float kick_body = osc_kick.Process() * env_a;

        noise_click.SetAmp(click_val); 
        filt_click.Process(noise_click.Process());
        float kick_click = filt_click.High() * env_click.Process();
        
        float raw_bass = osc_bass.Process();
        
        // SIDECHAIN (Seulement si l'enveloppe du kick est active)
        float ducking = 1.0f - (env_a * sidechain_val);
        if (ducking < 0.0f) ducking = 0.0f;
        
        // Si pas de kick (silence du séquenceur), la basse remplit l'espace !
        // C'est ça qui crée le groove "Call & Response"
        float final_bass = raw_bass * (ducking * ducking) * 0.4f;

        float mix = kick_body + kick_click + final_bass;
        float output = SoftClip(mix, 1.0f + (drive_val * 4.0f));

        out[0][i] = output;
        out[1][i] = output;
    }
}

void setup() {
    delay(1000); 
    Serial.begin(9600);
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    float sr = DAISY.get_samplerate();

    pinMode(MUX_S0, OUTPUT); pinMode(MUX_S1, OUTPUT);
    pinMode(MUX_S2, OUTPUT); pinMode(MUX_S3, OUTPUT);

    osc_kick.Init(sr); osc_kick.SetWaveform(Oscillator::WAVE_SIN);
    env_pitch_kick.Init(sr); env_pitch_kick.SetTime(ADENV_SEG_DECAY, 0.05f); env_pitch_kick.SetMax(1.0f);
    env_amp_kick.Init(sr); env_amp_kick.SetTime(ADENV_SEG_DECAY, 0.3f);
    noise_click.Init(); filt_click.Init(sr); filt_click.SetFreq(2500.0f); filt_click.SetRes(0.2f);
    env_click.Init(sr); env_click.SetTime(ADENV_SEG_DECAY, 0.02f);
    osc_bass.Init(sr); osc_bass.SetWaveform(Oscillator::WAVE_TRI);
    
    // IMPORTANT : Metro réglé sur les doubles-croches (16th notes)
    // BPM / 60 = Battements par seconde. * 4 = Pas par seconde.
    metro.Init((126.0f / 60.0f) * 4.0f, sr); 

    DAISY.begin(AudioCallback);
}

void loop() {
    // --- LECTURE ---
    float c0 = readMux(0); // Tune
    float c1 = readMux(1); // Sidechain
    float c2 = readMux(2); // Decay
    float c3 = readMux(3); // Click
    float c4 = readMux(4); // Drive
    
    // NOUVEAU : C5 = SÉLECTEUR DE PATTERN
    float c5 = readMux(5); 
    
    // Mapping
    osc_bass.SetFreq(35.0f + (c0 * 60.0f));
    sidechain_val = c1 * 1.5f;
    env_amp_kick.SetTime(ADENV_SEG_DECAY, 0.1f + (c2 * 0.5f));
    click_val = c3;
    drive_val = c4;
    
    // Sélecteur de Pattern (Divise le potard en 5 zones)
    // c5 est entre 0.0 et 1.0. On multiplie par 4.9 pour avoir 0,1,2,3,4
    selected_pattern = (int)(c5 * (NUM_PATTERNS - 0.1f));

    // Debug
    Serial.print("Pattern: "); Serial.print(selected_pattern);
    Serial.print(" | Step: "); Serial.println(current_step);
    
    delay(50);
}
