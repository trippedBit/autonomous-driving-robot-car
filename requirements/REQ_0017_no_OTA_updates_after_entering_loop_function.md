**ID**: REQ_0017

**Status**: In specification

**Type**: Functional

**Description**:<br>
OTA function shall use self-check's SELF_CHECK_PASSED attribute and attribute LOOP_FUNCTION_ENTERED (type boolean) to ensure, function is only called after successfull self-check but before entering loop function which would start movement.

The following configurable parameters of type string shall be provided:
- LOOP_FUNCTION_ENTERED, type boolean, default value true (fail-safe)

LOOP_FUNCTION_ENTERED shall be set to true as soon as loop function is entered.