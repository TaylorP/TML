# TPML
Taylor Markup Language(TML) is a markup language I use for [my blog and personal website](http://www.taylorpetrick.com). Since my blogging platform prefers statically generate content, I needed a tool to produce HTML blobs for posts. For a while I wrote the HTML myself, but I've recently started converting quotes, apostrophes and dashes to their typographically correct Unicode values. I decided to write a tool to automate the process, as well as make it easier to write the posts.

The language is quite simple to parse. First, a pass is made over the whole document to extract `Function` and `Text` elements. Anything that isn't a function is assumed to be plain text. Functions are executed to output HTML blobs from their inputs, while text elements undergo additional processing to replace quotes, add URLs and perform styling like bold and italic. After processing, each text element is output in a `<p></p>` block as HTML.

# Usage and Contributing
I don't plan to merge any pull requests or guarantee support for the code. Any changes or improvements I make to the tool will be made available here on GitHub. Anyone is welcome to use it for their own projects, of course. Note that current implementation in GitHub still has a few issues which are covered below. These aren't really show-stoppers for me, but I will try to fix them.

# Functions
Utility functions that emit HTML can be defined in C++ and then used as follows:
```
@function(param1, param2, ...)
``` 
The following functions are included:
* @header("Title", "id")
* @image("annotation", "url1", "url2", ...)
* @code("language", "code")
* @latex("latex")

The output of the built-in functions are specific to the HTML used on my website, so I won't go into details of what they produce in terms of output.

# Inline syntax
Bold, italic and inline code elements are generated with the following syntax:
```
*bold*
_italic_
`inline code`
```

These produce the following HTML elements:
```
<b>bold</b>
<i>italic</i>
<span class='inline-code'></span>
```

# URL syntax
Urls are generated as follows:
```
[url-label](url-link)
```
An optional target parameter can also be included:
```
[url-label](url-link, target)
```
The target automatically has an underscored appended, so for example the following syntax:
```
[blog](http://www.taylorpetrick.com, blank)
```
would produce this html blob:
```
<a href='http://www.taylorpetrick.com' target='_blank'>blog</a>
```

# Symbol replacements
The following replacements are made to make quotes/dashes more typographically correct:
* apostrophe (') to &#8217 (&#8217;)

* open-single (') to &#8216 (&#8216;)
* closed-single (') to &#8217 (&#8217;)

* open-double (") to &#8220 (&#8220;)
* closed-double (") to &#8221 (&#8221;)

* en-dash (--) to &#8211 (&#8211;)
* em-dash  (---) to &#8212 (&#8212;)

# License
TML and the C++ parser are distributed under [The MIT License](https://opensource.org/licenses/MIT).