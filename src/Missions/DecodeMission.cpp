#include "Missions/DecodeMission.h"
#include "Tools/Base64.h"
#include "Tools/PcapAnalyzer.h"
#include "Tools/ROT13.h"
#include <iostream>

DecodeMission::DecodeMission() : 
    Mission("Decode Secret", 
           "Decrypt OmniCore's encoded messages",
           {ToolType::Base64}, 
           new PcapAnalyzer()) {}

bool DecodeMission::execute(const std::vector<Tool*>& tools) {
    std::cout << "\n=== МИССИЯ ДЕКОДИРОВКА ===\n";
    std::cout << "Расшифруйте секретное сообщение от руководителей OmniCore\n";
    
    const std::string encoded_msg = "VGhlIHNlY3JldCBwcm9qZWN0IGlzIE9NTklDT1JFX1gzOQ==";
    
    for (auto tool : tools) {
        if (tool->getType() == ToolType::Base64) {
            bool success = tool->execute(encoded_msg);
            if (success) {
                std::cout << "Расшифрованное сообщение раскрывает секретный проект: OMNI_CORE_X39!\n";
                return true;
            }
        }
    }
    
    std::cout << "Для этой миссии вам понадобится декодер Base64!\n";
    return false;
}