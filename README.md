# The xPack fork of qemu.git

This is a fork of <https://git.qemu.org/git/qemu.git> used to keep the customisations required by the xPack distribution.

The original README is available in the separate [README.rst](README.rst) file.

## Branches

- `master`: follows the upstream master
- `xpack`: includes the released code
- `xpack-develop`: includes work in progress
- `xpack-legacy`: the code used in the legacy GNU ARM Eclipse releases
- `xpack-legacy-develop`: development code for the legacy code

Development takes place in the `*-develop` branches and the code is merged in the corresponding branches during releases.

Eventual pull requests should be done against the `*-develop` branches.

## Changes

### Branded greeting

The greeting message was adjusted to read _xPack QEMU emulator version..._ ([d999f1e](https://github.com/xpack-dev-tools/qemu/commit/d999f1e2801f05a8a085b6e8ff6278bf526a8912)).

### Workaround to make the code build on macOS 10.13

Commit [7e3e20d8](https://github.com/xpack-dev-tools/qemu/commit/7e3e20d89129614f4a7b2451fe321cc6ccca3b76) from 23 June 2021 added support for clipboard on macOS, but the code requires macOS 10.14.

The topic was discussed on the [qemu-develop](https://lists.nongnu.org/archive/html/qemu-devel/2022-01/msg01395.html) mailing list.

The workaround was to conditionally compile the clipboard code only when building on macOS newer than 10.13 ([f0419314](https://github.com/xpack-dev-tools/qemu/commit/f04193145ab2800f1e871945e326bf2e5946095e)).
