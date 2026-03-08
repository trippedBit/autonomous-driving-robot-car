**ID**: REQ_0018

**Status**: In specification

**Type**: Functional

**Description**:<br>
The following configurable parameters of type string shall be used:
- OTA_FIRMWARE_URL
- OTA_FIRMWARE_MD5_URL

The update function shall compare downloaded MD5 and calculated firmware MD5 before applying the update.
The update shall only be applied if both MD5 checksums match.