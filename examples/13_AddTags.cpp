#include "ModIOInstance.h"

int main(void)
{
  modio::Instance mod(7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio::sleep(10);
      modioProcess();
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  // Let's start by requesting a single mod
  modio::Filter filter;
  filter.setFilterLimit(1);

  std::cout <<"Getting mods..." << std::endl;

  mod.getMods(NULL, filter, [&](void* object, const modio::Response& response, const std::vector<modio::Mod> & mods)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200 && mods.size() >= 1)
    {
      modio::Mod requested_mod = mods[0];
      std::cout << "Requested mod: " << requested_mod.name << std::endl;

      std::cout <<"Adding tags..." << std::endl;

      std::vector<std::string> tags;
      tags.push_back("Easy");

      // We add tags to a mod by providing the tag names. Remember, they must be valid tags allowed by the parrent game
      mod.addTags(NULL, requested_mod.id, tags, [&](void* object, const modio::Response& response, u32 mod_id, std::vector<modio::Tag> tags)
      {
        std::cout << "Add tags response: " << response.code << std::endl;
        if(response.code == 204)
        {
          std::cout << "Tags added successfully" << std::endl;
          for(int i=0; i < (int)tags.size(); i++)
          {
            std::cout << tags[i].name << std::endl;
          }
        }
        finish();
      });
    }
  });

  wait();

  modioShutdown();

  std::cout << "Process finished" << std::endl;

  return 0;
}
