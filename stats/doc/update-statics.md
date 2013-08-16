# Update statistics displayed by the stats table
In a previous steps we implemented the look and feel of the stats
table and found the way to update information about the plot type.
We integrated it in blacksmartie to check that it works. Now we
implement the functions that allow us to update the rest of the data
cells. We need to display the following information:

- Gate or plot type
- Channel names for the axes
- Stats
  - Mean
  - Median


## Set value for the gate type
In the same way as the plot type, we make two functions:
`select-gate-type` and `set-gate-type`:

```clojurescript
(defn select-gate-type
  "Returns CSS selector that addresses the table cells that display gate type."
  [gate-id]
  (str "table.statistics"
       (format " tr[data-gate-id=\"%s\"]" gate-id)
       " td[data-meaning=\"gate-type\"]"))

(defn set-gate-type!
  "Updates the cell that displays the gate type for the given gate.

   Parameters:

   - gate-id: ([1..4], int) What gate type to update
   - gate-type: (string) what to display as a gate type

   Example of usage:

       (set-gate-type! 1 'S')
       ;;=> will display 'S' in the type cell for gate 1.
   "
  [gate-id gate-type]
  (-> gate-id
      (select-gate-type)
      (css/sel)
      (dom/set-text! gate-type)))
```


Obviously, to make it work I need to annotate HTML:

```html
      <!-- Plot 1: Gate 1 -->
      <tr data-gate-id="1">
        <th>G1</th>
        <td data-meaning="gate-type">R</td>
        <td>11.1</td>
        <td>22.2</td>
        <td>33.3</td>
        <td>44.4</td>
      </tr>
```

I update the test function to run in a REPL:

```clojurescript
(defn test
  "Executes some functions in this file.

  Call this function from REPL to see how code behaves.
  "
  []
  (let  [first-id 1
         last-id 4
         ids (range first-id
                    (inc last-id))]

    ;; Sets all gate types to "PT-N", where N is plot id.
    (doseq [plot-id ids]
      (set-plot-type! plot-id (str "PT-" plot-id)))

    ;; Sets all gate types to "GT-N", where N is gate id.
    (doseq [gate-id ids]
      (set-gate-type! gate-id (str "GT-" gate-id)))

    ;; Test ended...
    ))
```

So, now we see `PT-` and `GT-` in all plots and gate type cells.

## Removing duplication
Unfortunately, by blindly copypasting the functions, we introduced 2
functions that are about the same except the type of selector.

For example, the function, `set-gate-type!` is practically the same as
`set-plot-type`, except it calls the `select-gate-type` instead of
`select-plot-type`.

This duplication will became worse as soon as we add new information
types and new operations. To resolve the issue, we can define general
operation `set-value!` that can take any selector, and put value to
it.

```clojurescript
(defn set-value!
  "Sets statistics value."
  [selector value]
  (-> selector
      (css/sel)
      (dom/set-text! value)))
```

And our two functions to set gate type and plot type are becoming:

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
  (set-value! (select-plot-type plot-id)
              plot-type))

(defn set-gate-type!
  "Updates the cell that displays the gate type for the given gate.

   Parameters:

   - gate-id: ([1..4], int) What gate type to update
   - gate-type: (string) what to display as a gate type

   Example of usage:

       (set-gate-type! 1 'S')
       ;;=> will display 'S' in the type cell for gate 1.
   "
  [gate-id gate-type]
  (set-value! (select-gate-type gate-id)
              gate-type))
```

This is better, but there is still some duplication. For example, the
semantic of the *type* both for plot and gate are similar - this is
string code for the type of object, only difference is that it
attributed for plot or for gate. In the current setting, if we want to
have separate selectors for gate and plot - it would mean implementing
many functions:

- for plots:
    - `set-plot-type!`
    - `set-plot-stat!`
    - `set-plot-channel!`
- then for gate:
    - `set-gate-type!`
    - `set-gate-stat!`
    - `set-gate-channel`

Here we have single semantical piece of information - *type*, and then
it is attributed for two contexts - for gates and for plots. I will
call this variation of semantics *attribution*.

If we imagine:

- `N`semantical chunks of information
- each semantical chunk can have `K` attributions
- and we want to support `M` operations

We would have an API of `N*M*K` functions to maintain. This is non ideal. In
fact, the meaning of the data - is the single obligatory  attribute
needed to address the cell. Thus, if we create one single function for
each semantical chunk, make this function to deal with all relevant
attributions, and then pass this to every operation, we will have API
of `N+M` functions to mainatin. Which is a lot less code to maintain!

This may sound a bit complicated, without concrete example. In our
particular case it means, that we will have only 5 functions:

- For semantic chunks:
    - `data-source-type`, with attributions:
        - `data-source-type`
        - `id`
    - `channel-label` with attributions
        - `data-source-type`
        - `id`
        - `axis`
    - `stat` with attributions:
        - `data-source-type`
        - `id`
        - `axis`
        - `meaning`

- For operations:
    - `set-value!`

Here I inroduce the following attributions:

- `data-source-type` - which tells if
   data come from plot or gate - and currently it can have 2 values -
  `:plot` or `:gate`.
- `id` - something that identifies the object, in our case one of
   `#{1 2 3 4}`, as we currently have 4 gates and 4 plots.
- `axis` - for 2 dimensional graphics, tells what axis is taken into
  account, can be `:x` or `:y`
- `meaning` - denots what kind of stats is displayed - may be one of
  `#{:median :mean}`


It means that instead of our 5 functions in our current
implementation:

- `set-value! [selector value]`
- `select-plot-type [plot-id]`
- `set-plot-type! [plot-id value]`
- `select-gate-type [gate-id]`
- `set-gate-type! [gate-id value]`

We will need only 2 functions:

- `data-source-type [plot-or-gate id]`
- `set-value! [selector value]`

So, this is how the new function `data-source-type` is implemented:

```clojurescript
(defn data-source-type
  "Addresses the table cells that display the type of the data source.

  Parameters:

  - `data-source-type` One of #{:plot :gate}
  - `id` Id of the data source
  "
  [data-source-type id]
  (str "table.statistics"
       (format " tr[data-%s-id=\"%s\"]"
               (name data-source-type)
               id)
       (format " td[data-meaning=\"%s-type\"]"
               (name data-source-type))))
```

This is a little bit more complicated - note the use of the `name`
function, that will transform the keyword, like `:gate` into the
string representation like `gate`. This would  generate attributes
that correspond to our HTML and CSS.

We also need to update our test:

```clojurescript
(defn test
  "Executes some functions in this file.

  Call this function from REPL to see how code behaves.
  "
  []
  (let  [first-id 1
         last-id 4
         data-source-types [:plot :gate]
         prefixes {:plot "PT-" :gate "gt-"}
         ids (range first-id
                    (inc last-id))
         label (fn [ds id]
                 (str (get prefixes ds "???" )
                      id))]

    ;; Sets all plot types to "PT-N", where N is plot id.
    ;; Sets all gate types to "gt-K", where K is gate id.
    (doseq [data-source data-source-types
            id ids]
      (print data-source id
             (label data-source id))
      (set-value! (data-source-type data-source id)
                    (label data-source id)))
      ;; Test ended...
      ))
```

## Set labels for channels
All what is needed is to annotate HTML:

```html

      <!-- Plot 4: Header -->
      <tr class="plot-header"
          data-plot-id="4">
        <th>Plot 4</th>
        <td data-meaning="plot-type">S</td>
        <td data-axis="x">FSC</td>
        <td data-axis="y">SSC</td>
        <td data-axis="x">FSC</td>
        <td data-axis="y">SSC</td>
      </tr>

```

Channel labels are displayed only in a plot headers. So, the function
that accesses them could be written like this:

```clojurescript
(defn channel-label
  "Addresses the cells that display the channel label for the given axis"
  [plot-id axis]
  (str "table.statistics"
       (format " tr.plot-header[data-plot-id=\"%s\"]"
               plot-id)
       (format " td[data-axis=\"%s\"]"
               (name axis) )))
```

## Display stats
In the same way, we annotate HTML and define how to access the cells
that display stats:

```html
       <tr data-gate-id="4">
        <th>G4</th>
        <td data-meaning="gate-type">R</td>
        <td data-meaning="mean"
            data-axis="x">11.1</td>
        <td data-meaning="mean"
            data-axis="y">22.2</td>
        <td data-meaning="median"
            data-axis="x">33.3</td>
        <td data-meaning="median"
            data-axis="y">44.4</td>
      </tr>
```

```clojurescript
(defn stat
  "Addresses the cells that display particular statistic information"
  [data-source-type id meaning axis]
  (str "table.statistics"
       (format " tr[data-%s-id=\"%s\"]"
               (name data-source-type)
               id)
       (format " td[data-meaning=\"%s\"][data-axis=\"%s\"]"
               (name meaning)
               (name axis))))
```

Then we test it all together:

```clojurescript
(defn test
  "Executes some functions in this file.

  Call this function from REPL to see how code behaves.
  "
  []
  (let  [data-source-types [:plot :gate]
         prefixes {:plot "PT-" :gate "gt-"}
         ids [1 2 3 4]
         axes [:x :y]
         meanings [:mean :median]
         label-data-source (fn [ds id]
                             (str (get prefixes ds "???" ) id))
         label-channel (fn [plot-id axis]
                         (str "CH-" plot-id "-" (name axis)))
         label-stat (fn [ds id meaning axis]
                      (str (get prefixes ds "???" )
                           id
                           ":" (name meaning)
                           ":" (name axis)))]

    ;; Sets all plot types to "PT-N", where N is plot id.
    ;; Sets all gate types to "gt-K", where K is gate id.
    (doseq [data-source data-source-types
            id ids]
      (print data-source id
             (label-data-source data-source id))
      (set-value! (data-source-type data-source id)
                    (label-data-source data-source id)))

    ;; Set all channel labels
    (doseq [plot-id ids
            axis axes]
      (set-value! (channel-label plot-id axis)
                  (label-channel plot-id axis)))

    ;; Set all stats
    (doseq [ds data-source-types
            id ids
            meaning meanings
            axis axes]
      (set-value! (stat ds id meaning axis)
                  (label-stat ds id meaning axis)))
      ;; Test ended...
      ))
```

The result should fill all table in a browser. Now we are ready to
integrate it into the blacksmartie.

