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





