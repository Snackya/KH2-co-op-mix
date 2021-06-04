# KH2 Co-op Mix

## Introduction
This software will make it so you can play KH2FM "cooperatively".  It was designed to be used with Sonicshadowsilver's Garden of Assemblage (GoA) mod and in a randomizer setting.

The GoA works as a central hub. Here you:
- bring your new checks from each world.  
- pick up checks from other players when you return.  
  
Things that get synched between players are:
- Chests
- Popup rewards (Sora only)
- Bonus level rewards (e.g. Cerberus fight reward) (Sora only)
- Level rewards (Sora only)
- Drive level rewards
- Levels (Sora only) (optional)
- Drive levels (optional)  

Currently unsupported:
- party related stuff
- world progress

## Usage
#### Server
One player will have to host a server with the corresponding .exe or their own solution. The `config.txt` is optional here and only used for setting a different `PORT`.
That player will have to share their IP (`SERVER_ADDRESS`) and (if changed from the default) `PORT` their server is running on.
**Notes:** 
- Port-forwarding may be required on your router.
- Make sure to allow the server through your windows firewall.

#### Clients
Started with `KH2 Co-op Mix.exe`.
Every player must set up the `config.txt` file correctly for the program to work (exclude the quotation marks).
- `SERVER_ADDRESS =`
the host's IP. (e.g. `100.110.120.130`). Host himself leaves this at `127.0.0.1`
- `PORT =` the hosts port (e.g. `7536`)
- `VERSION =` either `PS2` or `PC` depending on if you play via PCSX2 or on the PC release
- `SHARE_LEVELS =` either `1` or `0` depending on whether you want to share Sora's level or not
- `SHARE_DRIVES =` same as levels

When you start the `KH2 Co-op Mix.exe` make sure of the following:
- the `config.txt` is correctly set up and in the same folder
- the host's server is running
- the game is running


### Acknowledgements
- [Sonicshadowsilver2](https://github.com/sonicshadowsilver2) for creating the GoA mod and providing resources.
- [Num](https://github.com/1234567890num) for his resources and generally helping me out.
- [Tommadness](https://github.com/tommadness) for generally helping me out at times.