//
//  AudioLibSwitcher_applaudio.h
//  AudioLibSwitcher_applaudio
//
//  Created by Rasmus Anthin on 2025-09-15.
//

#pragma once
#include "../../AudioLibSwitcher/include/AudioLibSwitcher/IAudioLibSwitcher.h"
#include <applaudio/AudioEngine.h>
#include <memory>

namespace audio
{
  
  class AudioLibSwitcher_applaudio : public IAudioLibSwitcher
  {
  private:
    std::unique_ptr<applaudio::AudioEngine> engine;
    bool initialized = false;
    
  public:
    AudioLibSwitcher_applaudio() = default;
    ~AudioLibSwitcher_applaudio() override
    {
      finish();
    }
    
    virtual void init(bool enable_audio = true) override
    {
      if (initialized)
        return;
      
      engine = std::make_unique<applaudio::AudioEngine>(enable_audio);
      if (engine->startup())
        initialized = true;
    }
    
    virtual void finish() override
    {
      if (engine && initialized)
        engine->shutdown();
      initialized = false;
      engine.reset();
    }
    
    virtual unsigned int create_source() override
    {
      if (!initialized)
        return 0;
      return engine->create_source();
    }
    
    virtual void destroy_source(unsigned int src_id) override
    {
      if (initialized)
        engine->destroy_source(src_id);
    }
    
    virtual unsigned int create_buffer() override
    {
      if (!initialized)
        return 0;
      return engine->create_buffer();
    }
    
    virtual void destroy_buffer(unsigned int buf_id) override
    {
      if (initialized)
        engine->destroy_buffer(buf_id);
    }
    
    virtual void play_source(unsigned int src_id) override
    {
      if (initialized)
        engine->play_source(src_id);
    }
    
    virtual bool is_source_playing(unsigned int src_id) override
    {
      if (!initialized)
        return false;
      return engine->is_source_playing(src_id);
    }
    
    virtual void pause_source(unsigned int src_id) override
    {
      if (initialized)
        engine->pause_source(src_id);
    }
    
    virtual void stop_source(unsigned int src_id) override
    {
      if (initialized)
        engine->stop_source(src_id);
    }
    
    virtual void set_source_volume(unsigned int src_id, float vol) override
    {
      if (initialized)
        engine->set_source_volume(src_id, vol);
    }
    
    virtual void set_source_pitch(unsigned int src_id, float pitch) override
    {
      if (initialized)
        engine->set_source_pitch(src_id, pitch);
    }
    
    virtual void set_source_looping(unsigned int src_id, bool loop) override
    {
      if (initialized)
        engine->set_source_looping(src_id, loop);
    }
    
    virtual void set_source_standard_params(unsigned int src_id) override
    {
      if (initialized)
      {
        // Set standard parameters using your existing interface
        set_source_pitch(src_id, 1.0f);
        set_source_volume(src_id, 1.0f);
        set_source_looping(src_id, false);
      }
    }
    
    virtual bool set_buffer_data_8u(unsigned int buf_id, const std::vector<unsigned char>& buffer, int num_channels, int sample_rate) override
    {
      if (!initialized)
        return false;
        
      engine->set_buffer_data_8u(buf_id, buffer, num_channels, sample_rate);
      return true;
    }
    
    virtual bool set_buffer_data_16s(unsigned int buf_id, const std::vector<signed short>& buffer, int num_channels, int sample_rate) override
    {
      if (!initialized)
        return false;
        
      engine->set_buffer_data_16s(buf_id, buffer, num_channels, sample_rate);
      return true;
    }
    
    virtual bool set_buffer_data_32f(unsigned int buf_id, const std::vector<float>& buffer, int num_channels, int sample_rate) override
    {
      if (!initialized)
        return false;
        
      engine->set_buffer_data_32f(buf_id, buffer, num_channels, sample_rate);
      return true;
    }

    
    virtual void attach_buffer_to_source(unsigned int src_id, unsigned int buf_id) override
    {
      if (initialized)
        engine->attach_buffer_to_source(src_id, buf_id);
    }
    
    virtual void detach_buffer_from_source(unsigned int src_id) override
    {
      if (initialized)
        engine->detach_buffer_from_source(src_id);
    }
    
    virtual void init_3d_scene() override
    {
      if (initialized)
        engine->init_3d_scene();
    }

    virtual void enable_source_3d_audio(unsigned int src_id, bool enable) override
    {
      if (initialized)
        engine->enable_source_3d_audio(src_id, enable);
    }

    // std::array<float, 9> is a row-major 3x3 matrix.
    virtual bool set_source_3d_state_channel(
        unsigned int src_id, int channel,
        const std::array<float, 9>& rot_mtx,
        const std::array<float, 3>& pos_world, const std::array<float, 3>& vel_world) override
    {
      if (initialized)
        return engine->set_source_3d_state_channel(src_id, channel, rot_mtx, pos_world, vel_world);
      return false;
    }

    // std::array<float, 9> is a row-major 3x3 matrix.
    virtual bool set_listener_3d_state_channel(
        int channel,
        const std::array<float, 9>& rot_mtx,
        const std::array<float, 3>& pos_world, const std::array<float, 3>& vel_world) override
    {
      if (initialized)
        return engine->set_listener_3d_state_channel(channel, rot_mtx, pos_world, vel_world);
      return false;
    }
    
    virtual bool set_source_speed_of_sound(unsigned int src_id, float speed_of_sound) override
    {
      if (initialized)
        return engine->set_source_speed_of_sound(src_id, speed_of_sound);
      return false;
    }
    
    virtual std::optional<float> get_source_speed_of_sound(unsigned int src_id) override
    {
      if (initialized)
        return engine->get_source_speed_of_sound(src_id);
      return std::nullopt;
    }

    virtual bool set_source_attenuation_min_distance(unsigned int src_id, float min_dist) override
    {
      if (initialized)
        return engine->set_source_attenuation_min_distance(src_id, min_dist);
      return false;
    }
    
    virtual bool set_source_attenuation_max_distance(unsigned int src_id, float max_dist) override
    {
      if (initialized)
        return engine->set_source_attenuation_max_distance(src_id, max_dist);
      return false;
    }
    
    virtual bool set_source_attenuation_constant_falloff(unsigned int src_id, float const_falloff) override
    {
      if (initialized)
        return engine->set_source_attenuation_constant_falloff(src_id, const_falloff);
      return false;
    }
    
    virtual bool set_source_attenuation_linear_falloff(unsigned int src_id, float lin_falloff) override
    {
      if (initialized)
        return engine->set_source_attenuation_linear_falloff(src_id, lin_falloff);
      return false;
    }
    
    virtual bool set_source_attenuation_quadratic_falloff(unsigned int src_id, float sq_falloff) override
    {
      if (initialized)
        return engine->set_source_attenuation_quadratic_falloff(src_id, sq_falloff);
      return false;
    }
    
    virtual std::string check_error() override
    {
      // For applaudio, you might want to add error tracking
      // For now, return empty string meaning "no error"
      return "";
    }
    
  };

}
