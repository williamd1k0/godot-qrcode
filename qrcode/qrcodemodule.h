/* qrcodemodule.h */

#ifndef QRCODE_H
#define QRCODE_H

#include "core/reference.h"
#include "core/image.h"
#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "editor/property_editor.h"
#include "qrcode.h"

class QRCodeTexture : public Texture {
	GDCLASS(QRCodeTexture, Texture);

private:
	Ref<Image> data;
	RID texture;
	uint32_t flags;
	Vector2i size;

	QRCode qrcode;
	String text = "";
	uint8_t error_correction = ECC_LOW;
	uint8_t version = 1;

	bool update_pending;
	void _queue_update();
	void _update();
	Ref<Image> _gen_image(const String &p_text);

protected:
	static void _bind_methods();

public:
	int get_width() const;
	int get_height() const;

	virtual RID get_rid() const { return texture; }
	virtual bool has_alpha() const { return false; }
	virtual void set_flags(uint32_t p_flags) {};
	virtual uint32_t get_flags() const { return 0; }

	virtual Ref<Image> get_data() const;

	void set_text(const String &p_text);
	String get_text();
	void set_error_correction(uint8_t p_error_correction);
	uint8_t get_error_correction();
	void set_version(uint8_t p_version);
	uint8_t get_version();
	
	QRCodeTexture();
	virtual ~QRCodeTexture();
};

#endif // QRCODE_H