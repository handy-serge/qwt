# Update statistics displayed by the stats table
In a previous steps we implemented the look and feel of the stats
table and found the way to update information about the plot type.
We integrated it in blacksmartie to check that it works. Now we
implement the functions that allow us to update the rest of the data
cells.

## Update gate type
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
    (for [plot-id ids]
      (set-plot-type! plot-id (str "PT-" plot-id)))

    ;; Sets all gate types to "GT-N", where N is gate id.
    (for [gate-id ids]
      (set-gate-type! gate-id (str "GT-" gate-id)))

    ;; Test ended...
    ))
```

So, now we see `PT-` and `GT-` in all plots and gate type cells.
