//////////////////////////////////////////////////////
//discord.h // where discord intergration code goes //
//////////////////////////////////////////////////////

#include <assert.h>
#define DISCORD_REQUIRE(x) assert(x == DiscordResult_Ok)

void DISCORD_CALLBACK UpdateActivityCallback(void* data, enum EDiscordResult result) {
 DISCORD_REQUIRE(result);
}

void DISCORD_CALLBACK OnUserUpdated(void* data) {
 struct Application* app = (struct Application*)data;
 struct DiscordActivity activity;
 struct DiscordUser user;
 app->users->get_current_user(app->users, &user);
 app->user_id = user.id;
 
 uint8_t NumOfPlayers[5], Title[16];
 sprintf(NumOfPlayers, "(%i)", sys.NumOfPlayers);
 sprintf(Title, "%s", (uint8_t*)(sys.ROMloaded?(!sys.Title[0]?"No Title":sys.Title):"NO-ROM"));
 
 memset(&activity, 0, sizeof(activity));
 sprintf(activity.name, "TheGameRazer");
 sprintf(activity.details, "Prototype %s Alpha Build", version);
 sprintf(activity.state, "Status: %s [%s] %s%s", (uint8_t*)((!sys.ROMloaded)?"Idle":(sys.Debug)?"Debugging":(sys.Pause)?"Paused":"Playing"), Title,(uint8_t*)(sys.SoloPlay)?"Solo Play":(!sys.Online)?"Co-Op Play":"Online",(uint8_t*)(sys.SoloPlay)?"":NumOfPlayers);
 sprintf(activity.assets.large_image,"tgr-logo_");
 sprintf(activity.assets.small_image,"tgr-logo_alone_");
 sprintf(activity.assets.large_text,Title);
 sprintf(activity.assets.small_text,"TheGameRazer Prototype [Powered By Raylib]");
 activity.timestamps.start = sys.epoch;
 
 app->activities->update_activity(app->activities, &activity, app, UpdateActivityCallback);
}

void DISCORD_CALLBACK OnOAuth2Token(void* data, enum EDiscordResult result, struct DiscordOAuth2Token* token) {
 if (result == DiscordResult_Ok) {
  printf("OAuth2 token: %s\n", token->access_token);
 } else {
  printf("GetOAuth2Token failed with %d\n", (int)result);
 }
}

void DISCORD_CALLBACK OnLobbyConnect(void* data, enum EDiscordResult result, struct DiscordLobby* lobby) {
 printf("LobbyConnect returned %d\n", (int)result);
}