-- Static demo config for WAR2 v1.08 shareware (replaces wartool's runtime-generated wc2-config.lua).
-- wartool's end-of-extraction write path is bypassed under DemoMode survival patches.
wargus.tales = false
wargus.expansion = false
wargus.music_extension = ".mid"
wargus.bne = false
wargus.game_font_width = 14
SetFontCodePage(437)
InGameStrings = {}
-- [dusty-bytes] demo build flag: suppress attract-mode (demo01-04.smp recordings
-- reference full-game units absent from demo data → SDL function-table crash).
wargus.is_demo_build = true
