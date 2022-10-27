#ifndef DSP_HPP
#define DSP_HPP

#include "Iir.h"
#include "common/endian.hpp"
#include "biquad.hpp"

#include <vector>
#include <stdint.h>

namespace dsp
{
enum ChannelSelect
{
    MONO,
    LEFT,
    RIGHT
};

struct Channels
{
    double left;
    double right;
};

class DSP
{
public:
    DSP();

    template <typename T>
    void filter(char* buffer, size_t count, ChannelSelect channel_select, uint32_t rate)
    {
        if(not initialized)
        {
            initialize(rate);
        }
        T* bufferT = (T*)buffer;
        for (size_t n = 0; n < count; n+=2)
        {
            Channels channels;
            channels.left = static_cast<double>(endian::swap<T>(bufferT[n]));
            channels.right = static_cast<double>(endian::swap<T>(bufferT[n+1]));
            double signal = getChannel(channels, channel_select);
            bufferT[n] = endian::swap<T>(static_cast<T>(lowPass(signal)));
            bufferT[n+1] = endian::swap<T>(static_cast<T>(highPass(signal)));
        }          
    }

private:
    bool initialized = false;
    static const int filter_order_ = 4;
    static const int crossover_frequency_ = 2000;
    double low_pass_gain_ = 1.0; 
    double high_pass_gain_ = 0.8; 

    Iir::Butterworth::LowPass<filter_order_> low_pass_1_;
    Iir::Butterworth::LowPass<filter_order_> low_pass_2_;
    Iir::Butterworth::HighPass<filter_order_> high_pass_1_;
    Iir::Butterworth::HighPass<filter_order_> high_pass_2_;
    biquad::Biquad low_eq_ = biquad::Biquad(1.0, 1.9980361502732378, 
        -0.998086849938938, 1.008609175274779, -1.9980361502732378, 
        0.989477674664159);

    void initialize(uint32_t rate);
    double getChannel(Channels channels, ChannelSelect channel_select);
    double lowPass(double signal_in);
    double highPass(double signal_in);
    
};
} // namespace dsp
#endif