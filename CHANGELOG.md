# Changelog

## [1.0.1] - 2026-08-22

Renommage du fichier `Debug.h` → `Debug_Fo170.h` : le nom `Debug.h` entrait en conflit en compilation sous Windows avec le `debug.h` des frameworks ESP8266/ESP32. `library.properties`, `library.json` et `README.md` mis à jour en conséquence.

## [1.0.0] - 2026-08-12

Version initiale publiée.

- `LOG_INFO` / `LOG_ERROR` / `LOG_WARNING` : `Serial.printf` + émojis, injections automatiques de `fichier:ligne`.
- Indirection interne `LOG_*_AT(msg, file, line)` (variantes explicites utilisables).
- `LOG_DEBUG` (actif uniquement avec `DEBUG_VERBOSE`).
- `LOG_INFO_VALUE` / `LOG_ERROR_VALUE` : affichage `nom = valeur` avec `fichier:ligne`.
- `Serial_PRINTLN_VERBOSE` / `PRINTF_VERBOSE` (conditionnels `DEBUG_VERBOSE`).
- `BOOT_HALT(msg)` : arrêt volontaire documenté pour les ESP (watchdog → reset, exploité par boot_info).
- `#pragma once`.