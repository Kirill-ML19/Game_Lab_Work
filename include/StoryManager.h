#pragma once
#include <vector>
#include <string>

class StoryManager {
    size_t currentChapter = 0;
    std::vector<std::string> missionIntros = {
        R"(
        Глава 1: Пробуждение
        Ты просыпаешься в заброшенном техно-ангаре. На столе перед тобой ноутбук 
        с сообщением: "OmniCore скрывает проект X39. Взломай их системы, чтобы 
        раскрыть правду. Первая цель - почтовый сервер."
        )",

        R"(
        Глава 2: Зашифрованная переписка
        Получен доступ к почте. В письме обнаружен странный шифр:
        "VGhlIHNlY3JldCBwcm9qZWN0IGlzIE9NTklDT1JFX1gzOQ=="
        Нужно расшифровать это сообщение!
        )",

        R"(
        Глава 3: Сетевой след
        Расшифрованное сообщение указывает на подозрительный сетевой трафик.
        Требуется анализ пакетных данных для поиска координат секретного сервера.
        )",

        R"(
        Финал: Последний рубеж
        Координаты получены. Время для финального удара - взломать главный сервер
        OmniCore и обнародовать все данные.
        )"
    };

public:
    void showPrologue();
    void showMissionIntro(size_t missionId);
    void showChapter();
    void nextChapter();
    void showIntro(); 
    size_t getCurrentChapter() const; 
};
