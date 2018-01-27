#ifndef MODIO_MODCALLBACKS_H
#define MODIO_MODCALLBACKS_H

#include "Globals.h"
#include "wrappers/MinizipWrapper.h"
#include "wrappers/CurlWrapper.h"
#include "c/schemas/ModioResponse.h"
#include "c/schemas/ModioMod.h"
#include "ModUtility.h"

struct SubscribeModParams
{
  void* object;
  void (*callback)(void* object, ModioResponse response, ModioMod mod);
};

struct UnsubscribeModParams
{
  void* object;
  void (*callback)(void* object, ModioResponse response);
};

extern std::map< u32, SubscribeModParams* > subscribe_mod_callbacks;
extern std::map< u32, UnsubscribeModParams* > unsubscribe_mod_callbacks;

void modioOnSubscribeMod(u32 call_number, u32 response_code, json response_json);
void modioOnUnsubscribeMod(u32 call_number, u32 response_code, json response_json);

#endif