# cosmic absorbtion G4 simulation Toy
> A small toy that used for simulate the cosmic absorbtion in U238

[![NPM Version][npm-image]][npm-url]
[![Build Status][travis-image]][travis-url]
[![Downloads Stats][npm-downloads]][npm-url]


![](example.jpg)



## Installation

The Program is write and tested in UBUNTU 16.04

ROOT5.34.36[https://root.cern.ch/]
Geant4.10.03.p01[https://geant4.web.cern.ch]

To install ROOT AND Geant4
	You can use the small scrapt to install the grant4 and root if you didnot install those packages
	it will downloads and install and compile Geant4 automaticly
```
mkdir ROOT
cd ROOT
git clone https://github.com/Jiansiyu/cmake_geant4.git
cp cmake_geant4/cmake_geant4.sh ./
./cmake_geant4.sh 4.10.03.p01
```

Ubuntu
```sh
mkdir ${path}
cd ${path}
git clone https://github.com/Jiansiyu/g4cosmicAB.git
mkdir g4cosmicAB-build
cd g4cosmicAB-build
cmake ../g4cosmicAB
make -j4
```


## Usage example

Material of the TARGET
The source files are located in the 'src' folder. The material of the Target can be changed in 'MuonDetectorConstruction.cc'



## RUN EXAMPLES


```sh
make install
npm test
```

## Release History

* 0.2.1
    * CHANGE: Update docs (module code remains unchanged)
* 0.2.0
    * CHANGE: Remove `setDefaultXYZ()`
    * ADD: Add `init()`
* 0.1.1
    * FIX: Crash when calling `baz()` (Thanks @GenerousContributorName!)
* 0.1.0
    * The first proper release
    * CHANGE: Rename `foo()` to `bar()`
* 0.0.1
    * Work in progress

## Meta

Your Name – [@YourTwitter](https://twitter.com/dbader_org) – YourEmail@example.com

Distributed under the XYZ license. See ``LICENSE`` for more information.

[https://github.com/yourname/github-link](https://github.com/dbader/)

## Contributing

1. Fork it (<https://github.com/yourname/yourproject/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

<!-- Markdown link & img dfn's -->
[npm-image]: https://img.shields.io/npm/v/datadog-metrics.svg?style=flat-square
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics
[wiki]: https://github.com/yourname/yourproject/wiki