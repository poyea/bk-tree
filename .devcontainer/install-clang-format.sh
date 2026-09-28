#!/usr/bin/env bash
set -euo pipefail

installer="$(mktemp)"
trap 'rm -f "$installer"' EXIT

curl --proto '=https' --tlsv1.2 -fsSL https://apt.llvm.org/llvm.sh -o "$installer"
llvm_version="$(sed -n 's/^CURRENT_LLVM_STABLE=//p' "$installer" | head -n 1)"
if [[ -z "$llvm_version" ]]; then
  echo "Could not determine the latest stable LLVM version." >&2
  exit 1
fi

source /etc/os-release
codename="${UBUNTU_CODENAME:-${VERSION_CODENAME:-}}"
if [[ -z "$codename" ]]; then
  echo "Could not determine the Ubuntu release codename." >&2
  exit 1
fi

sudo apt-get update
sudo apt-get install -y ca-certificates curl gnupg
sudo install -d -m 0755 /usr/share/keyrings
curl --proto '=https' --tlsv1.2 -fsSL https://apt.llvm.org/llvm-snapshot.gpg.key \
  | gpg --dearmor \
  | sudo tee /usr/share/keyrings/apt.llvm.org.gpg >/dev/null

source_list="/etc/apt/sources.list.d/llvm-${llvm_version}.list"
if ! grep -RqsF "llvm-toolchain-${codename}-${llvm_version}" /etc/apt/sources.list.d; then
  printf 'deb [signed-by=/usr/share/keyrings/apt.llvm.org.gpg] https://apt.llvm.org/%s/ llvm-toolchain-%s-%s main\n' \
    "$codename" "$codename" "$llvm_version" \
    | sudo tee "$source_list" >/dev/null
fi

sudo apt-get update
sudo apt-get install -y "clang-format-$llvm_version"
sudo ln -sf "/usr/bin/clang-format-$llvm_version" /usr/local/bin/clang-format

clang-format --version