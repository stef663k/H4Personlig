from PIL import Image
import numpy as np


def get_metadata(image_path):
    with Image.open(image_path) as img:
        metadata = {
            "format": img.format,
            "mode": img.mode,
            "size": img.size,
            "palette": img.getpalette(),
            "info": img.info,
        }
    return metadata

print(get_metadata("OIP.jpg"))