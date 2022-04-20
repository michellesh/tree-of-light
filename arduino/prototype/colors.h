CRGB campfire[] = {
    CRGB::ForestGreen, CRGB::Lime,      CRGB::Gold,
    CRGB::DarkOrange,  CRGB::OrangeRed, CRGB::Maroon,
    CRGB::Chocolate,   CRGB::Coral,     CRGB::Lavender,
};

DEFINE_GRADIENT_PALETTE(heatmapGP){0,   0,   0,   0,     // black
                                   128, 255, 0,   0,     // red
                                   224, 255, 255, 0,     // bright yellow
                                   255, 255, 255, 255};  // full white
CRGBPalette16 heatmapPalette = heatmapGP;

DEFINE_GRADIENT_PALETTE(campfirePaletteGP){
    0,   campfire[0].r, campfire[0].g, campfire[0].b,
    127, campfire[2].r, campfire[2].g, campfire[2].b,
    255, campfire[4].r, campfire[4].g, campfire[4].b};
CRGBPalette16 campfirePalette = campfirePaletteGP;

//CRGBPalette16* activePalettes[] = {&campfirePalette, &heatmapPalette};
CRGBPalette16* activePalettes[] = {&campfirePalette};
