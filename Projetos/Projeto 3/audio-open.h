#include <stdint.h>
#ifndef _AUDIO_OPEN_
#define _AUDIO_OPEN_


typedef struct Music_header{

    unsigned char       riff_tag[4];

    uint32_t   riff_size;

    unsigned char       wave_tag[4],
                        form_tag[4];

    uint32_t            fmt_size;
    
    short               audio_format,
                        num_channels;

    uint32_t            sample_rate,
                        byte_rate;

    short               block_align,
                        bits_per_sample;
    
    unsigned char       data_tag[4];    

    uint32_t            data_size,
                        samples_channel;

    void                *DATA;
} Music_header;

// Função para carregar informações da stream indicada pelo ponteiro "caminho" 
// (NULL caso a saida desejada seja a entrada padrão) wave em structure indicada.
void audio_load(char *caminho, Music_header *wave); 

// Função para escrever informações da structure indicada em stream passada 
// por parâmetro por meio do ponteiro "caminho" (NULL caso a saida desejada seja a saida padrão).
void audio_set(char *caminho, Music_header *wave); 

#endif
