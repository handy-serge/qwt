(ns blacksmartie.client.stats
  "Updates statistics table.

  Statistics table displays the means and medians for the data displayed in gates and plots."
  (:require [domina :as dom]
            [domina.css :as css]
            [blacksmartie.client.stats.generate-html :refer [generate-html!]]
            [blacksmartie.client.stats.handle-user-input :refer [attach-event-listeners!]]))

;;; ## Data access ##
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

(defn channel-label
  "Addresses the cells that display the channel label for the given axis"
  [plot-id axis]
  (str "table.statistics"
       (format " tr.plot-header[data-plot-id=\"%s\"]"
               plot-id)
       (format " td[data-axis=\"%s\"]"
               (name axis))))

(defn stat-by-axis
  "Addresses the cells that display particular statistic
  information that can be qualified by axis."
  [data-source-type id meaning axis]
  (str "table.statistics"
       (format " tr[data-%s-id=\"%s\"]"
               (name data-source-type)
               id)
       (format " td[data-meaning=\"%s\"][data-axis=\"%s\"]"
               (name meaning)
               (name axis))))

(defn stat
  "Addresses the cells that display particular statistic
  information."
  [data-source-type id meaning]
  (str "table.statistics"
       (format " tr[data-%s-id=\"%s\"]"
               (name data-source-type)
               id)
       (format " td[data-meaning=\"%s\"]"
               (name meaning))))

;; ## Operations ##
(defn set-value!
  "Sets the values for the given statistic table region."
  [selector value]
  (dom/set-text! (css/sel selector)
                 value))


;;; ## Initialization ##
(defn initialize! []
  (generate-html!)
  (attach-event-listeners!)
  nil)



