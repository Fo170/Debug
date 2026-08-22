#pragma once

// ============================================================
// Debug_Fo170.h — Macros de log pour projets Arduino (header-only)
// Auteur : Olivier FOURNET (org Fo170) — Licence GPL-3.0-only
// Utilisation : #include "Debug_Fo170.h" (Serial doit être en portée)
// ============================================================

#ifdef DEBUG_VERBOSE
  #define Serial_PRINTLN_VERBOSE(x)    Serial.println(x)
  #define PRINTF_VERBOSE(x)    printf(x)
	//#define PRINTF_VERBOSE(x, y) printf(x, y)
#else
	#define Serial_PRINTLN_VERBOSE(x)    //Serial.println(x)
	#define PRINTF_VERBOSE(x)    //printf(x)
  //#define PRINTF_VERBOSE(x, y) //printf(x, y)
#endif

// --- Logs toujours compilés -----------------------------------
// Le fichier:ligne du point d'appel sont injectés automatiquement
// via une indirection (message -> LOG_*_AT) sans changer l'appelant.
#define LOG_INFO(msg)          LOG_INFO_AT(msg, __FILE__, __LINE__)
#define LOG_ERROR(msg)         LOG_ERROR_AT(msg, __FILE__, __LINE__)
#define LOG_WARNING(msg)       LOG_WARNING_AT(msg, __FILE__, __LINE__)

// --- Logs compilés uniquement si DEBUG_VERBOSE ----------------
#ifdef DEBUG_VERBOSE
  #define LOG_DEBUG(msg)       LOG_DEBUG_AT(msg, __FILE__, __LINE__)
#else
  #define LOG_DEBUG(msg)       //LOG_DEBUG(msg)
#endif

// --- Variantes _AT : fichier/ligne explicites -----------------
#define LOG_INFO_AT(msg, file, line)        Serial.printf("[INFO] 📄 %s (%s:%d)\n", msg, file, line)
#define LOG_ERROR_AT(msg, file, line)       Serial.printf("[ERROR] ❌ %s (%s:%d)\n", msg, file, line)
#define LOG_WARNING_AT(msg, file, line)     Serial.printf("[WARN] ⚠️ %s (%s:%d)\n", msg, file, line)
#define LOG_DEBUG_AT(msg, file, line)       Serial.printf("[DEBUG] 🐛 %s (%s:%d)\n", msg, file, line)

// --- Log valeur(s) : impression de variable + fichier:ligne ---
#define LOG_INFO_VALUE(name, val)           Serial.printf("[INFO] 📄 %s = %s (%s:%d)\n", name, String(val).c_str(), __FILE__, __LINE__)
#define LOG_ERROR_VALUE(name, val)          Serial.printf("[ERROR] ❌ %s = %s (%s:%d)\n", name, String(val).c_str(), __FILE__, __LINE__)

// BootInfo : fichier source et ligne de l'emplacement d'un arrêt volontaire.
// __FILE__/__LINE__ sont évalués la MACRO BOOT_HALT au point d'appel.
// BOOT_HALT(msg) : imprime l'emplacement (fichier.s:ligne) puis bloque.
// Le watchdog/panique ESP provoque ensuite un reset, et boot_info()
// (appelé au boot suivant) confirme le motif.
#define BOOT_HALT(msg) do { \
  Serial.println("-----------boot_halt-------------"); \
  Serial.print("At: "); Serial.print(__FILE__); Serial.print(":"); Serial.println(__LINE__); \
  if(msg){ Serial.print("Reason: "); Serial.println(msg); } \
  Serial.flush(); \
  while(1) {} \
} while(0)
