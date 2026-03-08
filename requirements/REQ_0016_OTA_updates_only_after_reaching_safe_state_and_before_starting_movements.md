**ID**: REQ_0016

**Status**: In specification

**Type**: Functional

**Description**:<br>
The following configurable parameters of type string shall be used:
- OTA_FIRMWARE_URL
- OTA_FIRMWARE_MD5_URL

Following conditions shall be applied:
- OTA check and update shall only be performed after successfull self-check, see [REQ_0010_first_function_shall_be_selfCheck.md](REQ_0010_first_function_shall_be_selfCheck.md)
- OTA function shall use self-check's SELF_CHECK_PASSED attribute and attribute LOOP_FUNCTION_ENTERED (type boolean) to ensure, function is only called after successfull self-check but before entering loop function which would start movement, see [REQ_0017_no_OTA_updates_after_entering_loop_function.md](REQ_0017_no_OTA_updates_after_entering_loop_function.md)
- OTA update shall only be applied if given and calculated MD5 match, see [REQ_0018_apply_OTA_update_only_when_MD5_matches.md](REQ_0018_apply_OTA_update_only_when_MD5_matches.md)


```mermaid
flowchart LR
    SelfCheck["successfull selfCheck"] -- apply OTA updates if needed --> Movement
```