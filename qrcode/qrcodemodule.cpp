/* qrcodemodule.cpp */

#include "qrcodemodule.h"


void QRCodeTexture::_queue_update() {
	if (update_pending)
		return;

	update_pending = true;
	call_deferred("_update");
}

void QRCodeTexture::_update() {
	update_pending = false;

	data = _gen_image(text);
	size = Vector2i(data->get_size());

	VS::get_singleton()->texture_allocate(texture, size.x, size.y, 0, Image::FORMAT_RGB8, VS::TEXTURE_TYPE_2D, 0);
	VS::get_singleton()->texture_set_data(texture, data);

	emit_changed();
}


Ref<Image> QRCodeTexture::_gen_image(const String &p_data) {
	Ref<Image> img;
	img.instance();

	// Allocate a chunk of memory to store the QR code
	const char *data = p_data.utf8().get_data();
	uint8_t qrcodeBytes[qrcode_getBufferSize(version)];
	qrcode_initText(&qrcode, qrcodeBytes, version, error_correction, data);

	int border_size = 1;
	img->create(qrcode.size+border_size*2, qrcode.size+border_size*2, false, Image::FORMAT_RGB8);
	img->fill(Color(1, 1, 1));

	img->lock();
	for (int y = 0; y < qrcode.size; y++) {
		for (int x = 0; x < qrcode.size; x++) {
			if (qrcode_getModule(&qrcode, x, y)) {
				img->set_pixel(x+border_size, y+border_size, Color(0, 0, 0));
			}
		}
	}
	img->unlock();
	return img;
}

int QRCodeTexture::get_width() const {
	return size.x;
}

int QRCodeTexture::get_height() const {
	return size.y;
}

Ref<Image> QRCodeTexture::get_data() const {
	return data;
}

void QRCodeTexture::set_text(const String &p_text) {
	text = p_text;
	_update();
	emit_changed();
}

String QRCodeTexture::get_text() {
	return text;
}

void QRCodeTexture::set_error_correction(uint8_t p_error_correction) {
	error_correction = p_error_correction;
	_update();
	emit_changed();
}

uint8_t QRCodeTexture::get_error_correction() {
	return error_correction;
}

void QRCodeTexture::set_version(uint8_t p_version) {
	version = p_version;
	_update();
	emit_changed();
}

uint8_t QRCodeTexture::get_version() {
	return version;
}

void QRCodeTexture::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_text", "text"), &QRCodeTexture::set_text);
	ClassDB::bind_method(D_METHOD("get_text"), &QRCodeTexture::get_text);

	ClassDB::bind_method(D_METHOD("set_error_correction", "error_correction"), &QRCodeTexture::set_error_correction);
	ClassDB::bind_method(D_METHOD("get_error_correction"), &QRCodeTexture::get_error_correction);

	ClassDB::bind_method(D_METHOD("set_version", "version"), &QRCodeTexture::set_version);
	ClassDB::bind_method(D_METHOD("get_version"), &QRCodeTexture::get_version);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text", PROPERTY_HINT_MULTILINE_TEXT), "set_text", "get_text");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "error_correction", PROPERTY_HINT_ENUM, "Low,Medium,Quartile,High"), "set_error_correction", "get_error_correction");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "version", PROPERTY_HINT_RANGE, "1,40,1"), "set_version", "get_version");
}

QRCodeTexture::QRCodeTexture() {
	size = Vector2i(21, 21);

	texture = VS::get_singleton()->texture_create();
	_queue_update();
}

QRCodeTexture::~QRCodeTexture() {
	VS::get_singleton()->free(texture);
}