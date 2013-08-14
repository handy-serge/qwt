# Look and fill
This document describes how to make statistics display look as described in requirements document.

## Change HTML to include all needed columns and lines
First, we add all needed fields for statistics display.

Statistics display is a table with 6 columns:

- Plot or gate name (header for the row)
- Plot or gate type
- Mean value for X axis
- Mean value for Y axis
- Median value for X axis
- Median value for Y axis


On a top of the table is the header.
Table has two types of rows. The first kind of rows is used to display the plot legend. It should be highlighted by having different text and background colors. It displays channel names for each axist. The rows of the second type display statistic values.

There is 4 plots, each plot has a header, plot information and one gate. Thus, we need 12 rows.

The code below shows the HTML needed to represent statistic display table:

```html
    <!-- Statics table -->
    <table class="statistics">
      <colgroup>
        <col></col>
        <col></col>
        <col></col>
        <col></col>
        <col></col>
        <col></col>
      </colgroup>
      <tr>
        <th></th>
        <th>Type</th>
        <th>Mean</br>(X)</th>
        <th>Mean</br>(Y)</th>
        <th>Med</br>(X)</th>
        <th>Med</br>(Y)</th>
      </tr>
      <!-- Plot 1 -->
      <!-- Plot 1: Header -->
      <tr class="plot-header">
        <th>Plot 1</th>
        <td>S</td>
        <td>FSC</td>
        <td>SSC</td>
        <td>FSC</td>
        <td>SSC</td>
      </tr>
      <!-- Plot 1: Stats -->
      <tr>
        <th>Plot 1</th>
        <td>S</td>
        <td>111.1</td>
        <td>222.2</td>
        <td>333.3</td>
        <td>444.4</td>
      </tr>
      <!-- Plot 1: Gate 1 -->
      <tr>
        <th>G1</th>
        <td>R</td>
        <td>11.1</td>
        <td>22.2</td>
        <td>33.3</td>
        <td>44.4</td>
      </tr>

      <!-- Plot 2 -->
  </table>
```

With the HTML in place, now we add CSS to make it look right.

## Adjust statistic presentation by using CSS
This section describes how CSS for statistics display is made.

### Attach CSS to HTML

First, we need to attach CSS to the HTML. I decided to put CSS in a separate file, called `stats.css`.

```html
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Statistics view page</title>
    <!--[if lt IE 9]>
    <script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
    <![endif]-->

       <!-- CSS from Blacksmartie. -->
       <link rel="stylesheet" href="css/handyem.css">

       <!-- Custom CSS for statistics display -->
       <link rel="stylesheet" href="css/stats.css">

       <!-- pointing to cljsbuild generated js file -->
       <script src="js/stats.js"></script>

  </head>
  <body>
    <!-- Rest of the page ... -->
  </body>
</html>
```

To associate stylesheet with the page, you just add a link with the attribute `rel` set to `"stylesheet"`. (In HTML5 the attribute value `type="text/css"` is no longer needed.)

### How to choose what to style
For each CSS rule it is needed to specify what it applies to by using selectors.

The statistics table is the first table of the blacksmartie application.
Theoretically I could style the table tag, but I do not know what kind of another tables could be added to application in a future. I could use separate ID to denote statistics table, but I already know that I will need similar table to display the counts. Therefore, I attach my styles by defining two classes:

- `statistics` - denotes statictical display;
- `plot-header` - allows to specify different colors to the row that display plot legend;

This is how styles are referenced in HTML:

```html
    <!-- Statics table -->
    <table class="statistics">
        <!-- ... -->
        <tr class="plot-header">
        <!-- ... -->
        </tr>
    </table>
```

Now we are ready to style the table

### CSS for statistics table
For statistics display we do the following in CSS:

- Collapse the borders of the table to save the screen space (`border-collapse: collapse`)
- Align numbers to the right (`text-aligh: right`)
- Put different colors on plot header (`background-color` and `color`)
- Set specific width to the columns (`width`)
- Align header text vertically (`vertical-aligh: top`)

It gives use the resulting  `stats.css` file:

```css
/* CSS styles for use when styling statistics tables */
table.statistics {
    border-collapse: collapse;
    text-align: right;
}

.statistics tr.plot-header {
    background-color:#EAD8D8;
    color: #CC0000;
}

.statistics col {
    width: 6em;
}

.statistics th {
    vertical-align: top;
}
```

## Fix broken REPL
The next step would be update ClojureScript code to reflect changes in HTML.
If we try to play with our code with browser REPL, we will find that browser
REPL no longer works! This is quite sad. Let's fix it.

After some bisecting, we find the reason why it is broken. Accidentally we moved infocation of the compiled ClojureScript in the `<head>` tag of the `<html>` instead of the `<body>` tag. For some strange reason, it breaks the connection!

So, we initiate the connection to the REPL so that it happens after the page is loaded.
We connect to the REPL from `onload` event.
This may be non-ideal if we would like to use REPL for debugging code that runs before
page fully loaded. If it will  become important, we could compile REPL code into separate
ClojureScript file and include it before the rest of JavaScript.

```clojurescript
(ns experiment.stats.brepl
  "Connection to the brower REPL server."
  (:require [clojure.browser.repl :as repl]))

(defn connect-repl
  " Connects to the server side component of ClojureScript browser REPL.

  It is assumed that REPL runs on a default port 9000"
  []
  (repl/connect "http://localhost:9000/repl"))


;; We connect to the REPL as soon as window loaded.
;;
;; I discovered, that browser REPL does not work if the compiled
;; JavaScript with REPL is included in the `<head>` instead of being
;; included in the `<body>`.
(set! (.-onload js/window) connect-repl)

```

## Update statiscs values from ClojureScript
So, now we have our table contain all needed information. The
structure of the table changed and our functions to set the cell
values no longer work.

New table contains several kinds of data:

- Information about plot types
- Information about gate types
- Information about what channel is displayed for what axis
- Information about means
    - for every axis
    - for every plot
    - for every gate
- Information about medians
    - for every axis
    - for every plot
    - for every gate

I want to hide this complexity from the client by providing separate
functions to deal with every type of data. This separates the
concerns, simplifies the client code and allows in a future to adjust
the statistics display without changes in Cytodyem.

### Public API for updating statistics table.
Let start with the plot types. The public API for displaying the plot
types is the single functio `set-plot-type!`. See the example of
invocation below:

```clojurescript
;; Will put the "S" in all cells of the table that display the plot
;; type for the plot 1
(set-plot-type! 1 "S")
```

The function takes plot id, and updates all needed cells. Thus, the
client do not need to know the structure of the statistics table.

To implement this function we need to map the semantics of the data
(this is a plot type), and what plot this information corresponds to
(plot 1) to the particular table cell (or cells) that should disply
this information. To achieve this we need some flexibility when
addressing table cells.


### Address particular cells in the HTML table
Basically, there are 3 approaches we could use:

- Associate unique id with each cell and than map semantic information
  to each id;
- Use implicit information about where each cell should be displayed
  (like this data are in a third row, second column)
- Annotate each cell with the semantic information and then to search
  for cells with the given annotations;

For example, assuming we need to display information about plot type
for the plot 1. This information is displayed in two places - in a
plot header and in a plot statistics. So, we map these cells with the
id:

```html
    <tr>
      <td id="plot-1-header-type">S</td>
    </tr>
    <tr>
      <td id="plot-1-stats-type">S</td>
    </tr>
```

And then we access it using the either directly by id, or via grouping
CSS selector. There is a variant of this approach, were instead of
using `id` attribute, the `class` attribute is used.


In second alternative, no annotation of HTML needed, but we assume
that the structure of the HTML is fixed, and address each cell by its
position, using XPath:

```xpath
/html/body/table/tbody/tr[2]/td
/html/body/table/tbody/tr[3]/td
```

Disadvantage of this approach, is that if the structure of the HTML is
changed, all XPath expressions need to be adjusted.


In the third approach, each peace of the semantic information is
attached where it is need, and then this information is used in
selectors. For example:

```html
<!-- The row contains information about plot 1: -->
<tr data-plot-id="1">
    ...
    <!-- The table cell contains information about the plot type: -->
    <td data-meaning="plot-type">S</td>
    ...
</tr>
```

Below are some reflections on advantages and disadvantages of each
approach:

- First approach seems a bit brittle because of id generation - you
  have to be sure that you generate them properly, and then, to select
  particular cell, you need to parse you ids back to get the value of
  the semantic parts;
- Second approach is less flexible if in a future the columns or rows
  are added, or table structure changes;
- Third aproach seems to be more manageable, as it allows to annotante
  some tags and then exploit the table structure. (For example, it is
  possible to annotate only table row, and then use this information
  for table cells within the row.)

### Annotating HTML table cells with semantic information
After some reflection I decided to go with the third approach.
This implies marking the HTML with the semantic attributes and the
using CSS selectors to access proper data.

Every table row that deals with the given plot has the attribute
`data-plot-id`. I decided to use the numbers `1, 2, 3, 4` as plot IDs
of the each plot.

Every table cell that contains information about plot type should have
atribute `data-meaning` set to `plot-type`.

The marked HTML now looks like this:

```html
    <!-- Statics table -->
    <table class="statistics">

      ... header ...

      <!-- Plot 1 -->
      <!-- Plot 1: Header -->
      <tr class="plot-header"
          data-plot-id="1">
        <th>Plot 1</th>
        <td data-meaning="plot-type"
            >S</td>
        <td>FSC</td>
        <td>SSC</td>
        <td>FSC</td>
        <td>SSC</td>
      </tr>
      <!-- Plot 1: Stats -->
      <tr data-plot-id="1">
        <th>Plot 1</th>
        <td data-meaning="plot-type">S</td>
        <td>111.1</td>
        <td>222.2</td>
        <td>333.3</td>
        <td>444.4</td>
      </tr>
      <!-- Plot 1: Gate 1 -->
      <tr>
        <th>G1</th>
        <td>R</td>
        <td>11.1</td>
        <td>22.2</td>
        <td>33.3</td>
        <td>44.4</td>
      </tr>

      ... more rows ...
    </table>
```

Please note that I marked with `data-plot-id` both rows - one that
contains the header, another that contains the statistics.

Then we need the way to set the value only to the cells that display
the plot type.

### Accessing specific cells using annotations
Given annotations described in a previous section, to access the plot
type cells for the first plot, we can use the following CSS selector:

```css
table.statistics tr[data-plot-id="1"] td[data-meaning="plot-type"]
```

It basically says: Find the statiscs table, in this table find all
rows annotated with plot id `1`, and in this rows look for the cells
with the meaning of `plot-type`.

This selector is generated by the following function:

```clojurescript
(defn select-plot-type
  "Returns CSS selector that addresses the table cells that display plot type."
  [plot-id]
  (str "table.statistics"
       (format " tr[data-plot-id=\"%s\"]" plot-id)
       " td[data-meaning=\"plot-type\"]"))
```

And the function to update the plot types using Domina css selectors:

```clojurescript
(defn set-plot-type!
  "Updates the cell that displays the plot type for the given plot.

   Parameters:

   - plot-id: ([1..4], int) What plot type to update
   - plot-type: (string) what to display as a plot type

   Example of usage:

       (set-plot-type! 1 'S')
       ;;=> will display 'S' in the type cell for plot 1.
   "
  [plot-id plot-type]
  (-> plot-id
      (select-plot-type)
      (css/sel)
      (dom/set-text! plot-type)))

```

To see that it works, load annotated HTML in the browser, and call the
functions in a REPL to see that the plot type changes for every 4
plots.

## Next steps
In the next step we will integrate the statistics display into
blacksmartie, to see how it looks in the real application and to try
to call the `set-plot-type!` function from Cytodyem.
