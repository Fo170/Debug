# Debug

![License](https://img.shields.io/badge/license-GPL--3.0--only-blue.svg) ![Arduino](https://img.shields.io/badge/framework-Arduino-00979D.svg)

Macros de debug **header-only** pour projets Arduino (ESP8266 / ESP32 / AVR / autres), en français.

- Auteur : [Olivier FOURNET](https://github.com/Fo170)
- Licence : [GPL-3.0-only](LICENSE)
- Architecture supportée : tout environnement avec `Serial` (ESP8266, ESP32, AVR, PIC Arduino…)

## Installation

**Copie directe** : déposer `Debug.h` à côté du fichier principal (`.ino`) ou dans le dossier `src/`.

**PlatformIO** (`lib_deps`) :
```ini
lib_deps =
    https://github.com/Fo170/Debug.git
```

**Arduino IDE** : via le gestionnaire de bibliothèques (recherche « Debug » Fo170) ou en copiant `Debug.h`/`library.properties` dans `libraries/Debug/`.

## Utilisation rapide

```c
#include <Arduino.h>
#include "Debug.h"

void setup() {
  Serial.begin(115200);

  LOG_INFO("Démarrage du système");      // [INFO] 📄 Démarrage du système (main.cpp:6)
  LOG_WARNING("Batterie faible");        // [WARN] ⚠️ Batterie faible (main.cpp:7)

  float tension = 3.62;
  LOG_INFO_VALUE("tension", tension);    // [INFO] 📄 tension = 3.62 (main.cpp:10)

  if (tension < 3.0) {
    LOG_ERROR("Sous-tension");           // [ERROR] ❌ Sous-tension (...)
    BOOT_HALT("undervoltage");           // blocage volontaire documenté
  }
}
```

## Macros

### Toujours compilés

| Macro | Sortie (moniteur série) |
|-------|--------------------------|
| `LOG_INFO(msg)` | `[INFO] 📄 msg (fichier:ligne)` |
| `LOG_WARNING(msg)` | `[WARN] ⚠️ msg (fichier:ligne)` |
| `LOG_ERROR(msg)` | `[ERROR] ❌ msg (fichier:ligne)` |
| `LOG_INFO_VALUE(nom, val)` | `[INFO] 📄 nom = val (fichier:ligne)` |
| `LOG_ERROR_VALUE(nom, val)` | `[ERROR] ❌ nom = val (fichier:ligne)` |
| `LOG_*_AT(msg, file, line)` | variante explicite (emplacement fourni manuellement) |
| `BOOT_HALT(msg)` | trace `fichier:ligne` + motif, puis `Serial.flush()` et `while(1)` |

`fichier:ligne` est injecté **automatiquement au point d'appel** (`__FILE__`/`__LINE__`) via l'indirection interne `LOG_*_AT(msg, file, line)` — qui reste utilisable directement pour un emplacement personnalisé.

### Compilés UNIQUEMENT si `#define DEBUG_VERBOSE` avant l'`#include`

```c
#define DEBUG_VERBOSE        // à placer AVANT #include "Debug.h"
#include "Debug.h"
```

| Macro | Effet |
|-------|-------|
| `LOG_DEBUG(msg)` | `[DEBUG] 🐛 msg (fichier:ligne)` |
| `Serial_PRINTLN_VERBOSE(x)` | `Serial.println(x)` |
| `PRINTF_VERBOSE(x)` | `printf(x)` (format seul, macro à 1 argument) |

Sans `DEBUG_VERBOSE`, ces appels sont **entièrement supprimés** du binaire (pas de trace de débogage en production).

`LOG_INFO` / `LOG_WARNING` / `LOG_ERROR` / `*_VALUE` restent actifs même en production (débogage permanent).

### `BOOT_HALT(msg)` — arrêt volontaire exploité au boot suivant

Affiche l'emplacement exact de l'arrêt puis bloque le µC :

```
-----------boot_halt-------------
At: main.cpp:18
Reason: undervoltage
```

Sur ESP (8266/32), le watchdog pendant `while(1)` force un **reset**. Au boot suivant, le module `boot_info` (du projet consommateur) peut relire le motif pour confirmer la cause de l'arrêt.

## Pièges & liens

- `Serial` doit être **en portée au point d'appel** : inclure `<Arduino.h>` (ou `"SerialWeb.h"` etc.) avant `Debug.h`.
- **UTF-8** : le fichier est encodé en UTF-8 (émojis 📄 ❌ ⚠️ 🐛) — le moniteur série doit être configuré en UTF-8 pour un affichage correct.
- `PRINTF_VERBOSE(x)` est un macro à **1 argument** (le format) : `PRINTF_VERBOSE("%d", v)` ne compile pas (la variante `(x, y)` est commentée dans le fichier).
- `LOG_*` passent le message en `%s` : passer une chaîne (pointeur `char*`/`const char*` ou littéral).
- `LOG_*_VALUE` convertit `val` via `String(val).c_str()` : le type `String` d'Arduino doit être disponible.

## Liens

- Dépôt : [github.com/Fo170/Debug](https://github.com/Fo170/Debug)
- Auteur / autres bibliothèques : [github.com/Fo170](https://github.com/Fo170)
