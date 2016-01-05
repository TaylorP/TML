# TML
Taylor Markup Language(TML) is a markup language I use for [my blog and personal website](http://www.taylorpetrick.com). Since my blogging platform prefers statically generate content, I needed a tool to produce HTML blobs for posts. For a while I wrote the HTML myself, but I've recently started converting quotes, apostrophes and dashes to their typographically correct Unicode values. I decided to write a tool to automate the process, as well as make it easier to write the posts.

The language is quite simple to parse. First, a pass is made over the whole document to extract `Function` and `Text` elements. Anything that isn't a function is assumed to be plain text. Functions are executed to output HTML blobs from their inputs, while text elements undergo additional processing to replace quotes, add URLs and perform styling like bold and italic. After processing, each text element is output in a `<p></p>` block as HTML.

## Disclaimer
I can't guarantee that I'll merge pull requests or provide support for the code indefinitetly. Any changes or improvements I make to the tool will be made available here on GitHub. Anyone is welcome to use it for their own projects, of course. Note that current implementation in GitHub still has a few issues which are covered below. These aren't really show-stoppers for me, but I will try to fix them.

## Building
Just run make in the checked out directory!
```
make
```

Additionally, you can use the `install` target to build the binary and place it in `/usr/local/bin`:
```
sudo make install
```

There are no build files for Windows or OS X, but it should be fairly straight forward to create them. Everything is written using the C++11 standard lib; there should be no platform specific code. Let me know if something doesn't work on another platform, though.

## Usage
To use TML simply write a document in the markup language, then parse the  it as follows:
```
./tml_parser input.tml
```
An example file `input.tml` is included in this repo. 

By default, the output is written to a file named `out.html` in the same directory. An alternative output file can be specified with the `-o` option. The `-f` option will attempt to strip newlines during output.
```
./tml_parser -f -o page.html page.tml
```

## Functions
Utility functions that emit HTML can be defined in C++ and then used as follows:
```
@function(param1, param2, ...)
``` 
The following functions are included:
* @header('Title', 'id')
* @image('annotation", 'url1', 'url2', ...)
* @code('language', 'code')
* @contents('name0', 'url0', 'name1', 'url1', ...)
* @latex('latex')
* @video('vimeo-id', 'width', 'height')

The output of the built-in functions are specific to the HTML used on my website, so I won't go into details of what they produce in terms of output.

## Inline syntax
Bold, italic and inline code elements are generated with the following syntax:
```
*bold*
_italic_
`inline code`
^super script^
%numeric span%
```

These produce the following HTML elements:
```
<b>bold</b>
<i>italic</i>
<span class='inline-code'></span>
```

## URL syntax
Urls are generated as follows:
```
[url-label]{url-link}
```
An optional target parameter can also be included:
```
[url-label]{url-link target}
```
For example the following syntax:
```
[blog]{http://www.taylorpetrick.com _blank}
```
would produce this html blob:
```
<a href='http://www.taylorpetrick.com' target='_blank'>blog</a>
```

## Symbol replacements
The following replacements are made to make quotes/dashes more typographically correct:
* apostrophe `'` to &#8217; `&#8217;`

* open-single `'` to &#8216; `&#8216;`
* closed-single `'` to &#8217; `&#8217;`

* open-double `"` to &#8220; `&#8220;`
* closed-double `"` to &#8221; `&#8221;`

* en-dash `--` to &#8211; `&#8211;`
* em-dash  `---` to &#8212; `&#8212;`

## Escape syntax
If a `\` character is put before any of the special characters or quotes, that character or quote will not be parsed or replaced. It'll be treated as a regular symbol.

## Issues
Since the parsing and replacement is quite simple (no parse tree, no context), there are a few potential parse issues that can arise.

Functions must start on their own line and cannot be embedded in text. This isn't really an issue, but a limitation that doesn't affect my usage.

Apostrophes (') and single quotes (') are the same ASCII character. That means this phrase:
```
'Nice quotes'
```
Could be confusing to the replacer. `Quotes'` could be plural ownership, or it could be the end of a string wrapped in single-quotes. I try to handle this intelligently in the `ApostropheReplacer`, but there might be some cases that aren't covered. TL;DR: be mindful of using single quote wrapped strings in the same block as apostrophes. Double quotes are always fine.


## License
TML and the C++ parser are distributed under [The MIT License](https://opensource.org/licenses/MIT).