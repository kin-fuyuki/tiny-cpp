pkgname=tiny

pkgver=1.0

pkgrel=1

pkgdesc="tiny script runner"

arch=('any')

url="https://crystalsoft.neocities.org"

license=('AGPL3')

makedepends=('gcc')

source=("https://github.com/J-K-Tech/${pkgname}/archive/refs/tags/${pkgver}.tar.gz")

sha256sums=('2af3bfa2937e7452f74895db7e12c60b67000dc9c2e9f1aa1e53f7e1537d2636')


build() {

cd "${srcdir}/${pkgname}-${pkgver}"
g++ -O3 src/term.cpp src/main.cpp -o tiny

}


package() {
cd "${srcdir}/${pkgname}-${pkgver}"
install -Dm755 tiny "$pkgdir/usr/bin/tiny"
} 