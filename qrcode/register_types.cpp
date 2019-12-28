/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "qrcodemodule.h"

void register_qrcode_types() {
	ClassDB::register_class<QRCodeTexture>();
}

void unregister_qrcode_types() {
   // Nothing to do here in this example.
}