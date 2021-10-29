#include "AudioTrack.hpp"

std::vector<AudioTrack*> AudioTrack::tracks;

AudioTrack::AudioTrack(std::string filename) {
	source = new AudioSource(filename);
	playing = false;
	offset = 0;
    tracks.push_back(this);
}

AudioTrack::~AudioTrack() {
    delete source;
    tracks.erase(std::remove(tracks.begin(), tracks.end(), this), tracks.end());
}

void AudioTrack::play() {
    playing = true;
}

void AudioTrack::play(float sec) {
    offset = (size_t)((double) sec * source->sps);
}

void AudioTrack::pause() {
    playing = false;
}
/*
void AudioTrack::audio44100(void* userdata, uint8_t* stream, int len) {
    len >>= 1;
    int16_t* buf = (int16_t*)stream;
    memset(buf, 0, len * sizeof(*buf));

    for (AudioTrack *t : tracks) {
        if (!t->playing) continue;
        size_t L = t->source->samples;
        int l = (t->offset + len) > L ? L - t->offset : len;
        for (int i = 0; i < l; i++)
            buf[i] += t->source->stream[t->offset + i];
        t->offset += l;
    }
    return;
}

void AudioTrack::audio48000(void* userdata, uint8_t* stream, int len) {
    len >>= 1;
    int16_t* buf = (int16_t*)stream;
    memset(buf, 0, len * sizeof(*buf));

    for (AudioTrack* t : tracks) {
        if (!t->playing) continue;
        size_t L = t->source->samples;
        int l = (t->offset + len) > L ? L - t->offset : len;
        for (int i = 0; i < l; i++)
            buf[i] += t->source->stream[t->offset + i];
        t->offset += l;
    }
    return;
}
*/

static int16_t mix(int16_t s1, int16_t s2) {
    int a = s1, b = s2, m;
    a += 32768, b += 32768;
    if ((a < 32768) && (b < 32768))
        m = a * b / 32768;
    else m = 2 * (a + b) - (a * b) / 32768 - 65536;
    if (m == 65536) m = 65535;
    m -= 32768;
    return (int16_t)m;
}

void AudioTrack::audio(int hz, int16_t* stream, int len) {
    memset(stream, 0, (size_t) len << 1);
    for (AudioTrack* t : tracks) {
        // Either it is not playing, or wrong sample rate for this buffer
        if (!t->playing || t->source->sps != hz) continue;
        size_t L = t->source->samples;
        int l = (t->offset + len) > L ? L - t->offset : len;
        for (int i = 0; i < l; i++)
            stream[i] = mix(stream[i], t->source->stream[t->offset + i]);
        t->offset += l;
    }
    return;
}

