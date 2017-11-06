#ifndef MODIO_IMAGE_METHODS_H
#define MODIO_IMAGE_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Image.h"
#include "Globals.h"
#include "Filter.h"

extern "C"
{
  void MODIO_DLL modioDownloadImageThumbnail(ModioImage *image, string path, void (*callback)(ModioResponse* response, char* path));
  void MODIO_DLL modioDownloadImageFull(ModioImage *image, string path, void (*callback)(ModioResponse* response, char* path));
  //void MODIO_DLL downloadModMediaImagesThumbnail(Mod *mod, function< void(int response_code, string message, Mod* mod, vector<string> paths) > callback);
  //void MODIO_DLL downloadModMediaImagesFull(Mod *mod, function< void(int response_code, string message, Mod* mod, vector<string> paths) > callback);
}

#endif