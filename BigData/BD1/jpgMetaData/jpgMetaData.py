from PIL import Image
from PIL.ExifTags import TAGS
import numpy as np


# def get_metadata(image_path):
#     with Image.open(image_path) as img:
#         metadata = {
#             "format": img.format,
#             "mode": img.mode,
#             "size": img.size,
#             "palette": img.getpalette(),
#             "info": img.info,
#         }
#     return metadata

# print(get_metadata("IMG_20241127_114318.jpg"))

# def get_exif(image_path):
#     with Image.open(image_path) as img:
#         exif = img._getexif()
#         if exif is not None:
#             exif = {
#                 TAGS.get(tag, tag): value
#                 for tag, value in exif.items()
#             }
#     return exif

# print(get_exif("IMG_20241127_114318.jpg"))
image = Image.open("IMG_20241127_114318.jpg")

exifData = image._getexif()

for tag_id in exifData:
    tag = TAGS.get(tag_id, tag_id)
    data = exifData.get(tag_id)

    if isinstance(data, bytes):
        data = data.decode()
    print(f"{tag:25}: {data}")

print(image.size)
print(image.mode)
print(image.format)
print(image.palette)  




