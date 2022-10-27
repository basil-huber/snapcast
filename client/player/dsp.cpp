#include "dsp.hpp"

namespace dsp
{
DSP::DSP()
{
};

void DSP::initialize(uint32_t rate)
{
    low_pass_1_.setup(rate, crossover_frequency_);
    low_pass_2_.setup(rate, crossover_frequency_);
    high_pass_1_.setup(rate, crossover_frequency_);
    high_pass_2_.setup(rate, crossover_frequency_);
    initialized = true;
}

double DSP::getChannel(Channels channels, ChannelSelect channel_select)
{
    double signal = 0;
    switch (channel_select)
    {
    case MONO:
        signal = (channels.right/2.0 + channels.left/2.0);
        break;
    case LEFT:
        signal = channels.left;
        break;
    case RIGHT:
        signal = channels.right;
        break;
    default:
        break;
    }
    return signal;
}

double DSP::lowPass(double signal_in)
{
    double signal_out;
    signal_out = low_pass_1_.filter(signal_in);  
    signal_out = low_pass_2_.filter(signal_out); 
    signal_out = low_eq_.filter(signal_out);
    return low_pass_gain_*signal_out;       
}

double DSP::highPass(double signal_in)
{
    double signal_out;
    signal_out = high_pass_1_.filter(signal_in);  
    signal_out = high_pass_2_.filter(signal_out); 
    return high_pass_gain_*signal_out;       
}

} // namespace dsp