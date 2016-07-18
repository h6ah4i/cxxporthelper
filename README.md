cxxporthelper
============

"cxxporthelper": Portable code helper library for C++.

This library is a part of the cxxdasp and the OpenSLMediaPlayer libraries.

This small library provides these features;

- Compile-time compiler type detection
- Some complement C++11 features support that are not provided by STLPort (intended to use with Android NDK)
- Some C++11 keywords compatible macros that are not supported by Visual Studio 2013
- Runtime CPU specific feature detection  (ex. SSE instructons)

How to build
---

```bash
mkdir build
cd build
cmake ..
make
```

Latest version
---

- Version 0.5.2  (July 18, 2016)


License
---

See [`LICENSE`](LICENSE) for full of the license text.

    Copyright (C) 2014 Haruki Hasegawa

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
