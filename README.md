# Ampel

Ampel simuliert eine Fußgängerampel in der Windows-Konsole. Auf Tastendruck schaltet die Simulation den Autoverkehr über Gelb auf Rot, gibt den Fußgängern Grün und kehrt anschließend zur normalen Verkehrsphase zurück.

## Bauen

Voraussetzungen sind Windows, CMake ab Version 3.16 und ein C-Compiler wie MinGW-w64 oder MSVC.

~~~powershell
cmake -S . -B build
cmake --build build
~~~

Starte `build\Ampel.exe`. Bei einem Mehrkonfigurationsgenerator wie Visual Studio liegt das Programm in einem Unterordner wie `build\Debug`.

## Bedienen

- **T** fordert Fußgängergrün an.
- **Q** beendet das Programm.
- Beide Tasten wirken ohne Eingabetaste. `[O]` kennzeichnet eine leuchtende Lampe, `[.]` eine ausgeschaltete.
