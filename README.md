# Godot QRCode

> :warning: DO NOT USE THIS MODULE IN PRODUCTION BEFORE REVIEWING THE CODE! :warning:

Experimental QRCode generation for Godot Engine.

This cpp module exposes a dynamic Texture (QRCodeTexture).

QRCode lib: https://github.com/ricmoo/QRCode

Known issues:
- Version check is not implemented, so Godot will crash if the input text is too big for the selected version (check version table in the lib page);
- Experimental code (I'm not a c++ expert);


Feel free to fork and fix/implement anything.