**ID**: REQ_0012

**Status**: In specification

**Type**: Non-Functional

**Description**:<br>
With each release, the version information shall be updated.<br>
Only increments are allowed, a new version can never be lower than the previous one.

Following rules shall apply in following order:
1. Major version number shall be incremented when the update contains a breaking change.
2. If major version number gets incremented, minor version number and patch version number shall be set to zero, e.g. "1.3.5" becomes "2.0.0".
3. Minor version number shall be incremented when the update adds new features and no changes are breaking. Else rules one and two apply.
4. If minor version number gets incremented, major version number shall stay unchanged and patch version number shall be set to zero, e.g. "1.3.5" becomes "1.4.0".
5. Patch version number shall be incremented, when the update only fixes bugs without adding new features and without breaking changes. If there are new features or breaking changes, rules one to four apply.
6. If patch version number gets incremented, both major version number and minor version number shall stay unchanged, e.g. "1.3.5." becomes "1.3.6".
