#include "json.hpp"
#include <curlpp/Easy.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <iostream>
#include <sstream>
#include <string>

using json = nlohmann::json;

const std::string BASE_URL = "https://na1.api.riotgames.com/lol/";
const std::string KEY = "RGAPI-dbdfb1b4-3a82-499b-b914-7388659e866e";

std::string invoke(const std::string &url) {
  curlpp::Cleanup clean;
  curlpp::Easy r;
  r.setOpt(new curlpp::options::Url(url));

  std::ostringstream response;
  r.setOpt(new curlpp::options::WriteStream(&response));

  r.perform();

  return std::string(response.str());
}

void get(const std::string &id) {
  json curr =
      json::parse(invoke(BASE_URL + "spectator/v3/active-games/by-summoner/" +
                         id + "?api_key=" + KEY));
  for (const auto &part : curr["participants"]) {
    json rank = invoke(BASE_URL + "league/v3/positions/by-summoner/" +
                       part["summonerId"].dump() + "?api_key=" + KEY);
    std::cout << part["summonerName"];
    for (const auto &w : rank) {
      for (const auto &s : w) {
        std::cout << s << '\n\n';
        auto tier = s.find("tier");
        auto rank = s.find("rank");
        if (tier != s.end()) {
          std::cout << s["tier"] << ": " << s["rank"] << std::endl;
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  std::string url =
      BASE_URL + "summoner/v3/summoners/by-name/WindFan?api_key=" + KEY;

  json ret = json::parse(invoke(url));
  get(ret["id"].dump());
  return 0;
}
