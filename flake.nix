{
  description = "An emulator for the 6502 chip";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    ftxui.url = "github:ArthurSonzogni/FTXUI";
  };

  outputs = { self, nixpkgs, ftxui }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
      llvm = pkgs.llvmPackages_latest;
    in {
      devShells.${system}.default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [ cmake clang-tools llvm.clang ];
        buildInputs = [ ftxui.packages.${system}.ftxui ];
      };
    };
}
