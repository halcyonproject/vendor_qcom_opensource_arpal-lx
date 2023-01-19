/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef HOTWORD_INTERFACE_H
#define HOTWORD_INTERFACE_H

#include "VoiceUIInterface.h"
#include "SoundTriggerEngine.h"

class HotwordInterface: public VoiceUIInterface {
  public:
    HotwordInterface(std::shared_ptr<VUIStreamConfig> sm_cfg);
    ~HotwordInterface();

    static int32_t ParseSoundModel(std::shared_ptr<VUIStreamConfig> sm_cfg,
                                   struct pal_st_sound_model *sound_model,
                                   st_module_type_t &first_stage_type,
                                   std::vector<sm_pair_t> &model_list);

    int32_t ParseRecognitionConfig(Stream *s,
                                   struct pal_st_recognition_config *config) override;

    void GetWakeupConfigs(Stream *s,
                          void **config, uint32_t *size) {}
    void GetBufferingConfigs(Stream *s,
                             uint32_t *hist_duration,
                             uint32_t *preroll_duration) override;
    void GetSecondStageConfLevels(Stream *s,
                                  listen_model_indicator_enum type,
                                  uint32_t *level) {}

    void SetSecondStageDetLevels(Stream *s,
                                 listen_model_indicator_enum type,
                                 uint32_t level) {}

    int32_t ParseDetectionPayload(Stream *s, void *event, uint32_t size) override;

    Stream* GetDetectedStream(void *event) override;

    void* GetDetectionEventInfo(Stream *s) { return nullptr; }

    int32_t GenerateCallbackEvent(Stream *s,
                                  struct pal_st_recognition_event **event,
                                  uint32_t *event_size, bool detection) override;

    void ProcessLab(void *data, uint32_t size) {}

    void UpdateFTRTData(void *data, uint32_t size) {}

    bool IsQCWakeUpConfigUsed() { return false; }

    int32_t UpdateEngineModel(Stream *s,
                              uint8_t *data,
                              uint32_t data_size,
                              struct detection_engine_config_voice_wakeup *wakeup_config,
                              bool add) { return 0;}

    int32_t UpdateMergeConfLevelsPayload(SoundModelInfo* src_sm_info,
                                         bool set) { return 0;}

    void GetKeywordIndex(Stream *s, uint32_t *start_index, uint32_t *end_index) {};

    void GetKeywordStats(Stream *s, uint64_t *start_ts,
                         uint64_t *end_ts, uint64_t *ftrt_duration) {};

    void UpdateIndices(Stream *s, uint32_t start_idx, uint32_t end_idx) {};

  protected:
    uint8_t *custom_event_;
    uint32_t custom_event_size_;
};

#endif
