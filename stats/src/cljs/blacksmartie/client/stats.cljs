(ns blacksmartie.client.stats
  "Updates statistics table.

  Statistics table displays the means and medians for the data displayed in gates and plots."
  (:require [domina :as dom]
            [domina.css :as css]
            [blacksmartie.client.stats.generate-html :refer [generate-html!]]
            [blacksmartie.client.stats.handle-user-input :refer [attach-event-listeners!]]
            [blacksmartie.client.stats.operations :as operations]))

;;; ## Data access ##
(defn data-source-type
  "Addresses the table cells that display the type of the data source.

  Parameters:

  - `data-source-type` One of #{:plot :gate}
  - `id` Id of the data source
  "
  [data-source-type id]
  (operations/DataSourceType. data-source-type id))

(defn channel-label
  "Addresses the cells that display the channel label for the given axis"
  [plot-id axis]
  (operations/ChannelLabel. plot-id axis))

(defn stat-by-axis
  "Addresses the cells that display particular statistic
  information that can be qualified by axis."
  [data-source-type id meaning axis]
  (operations/StatisticParameter2D. data-source-type id meaning axis))

(defn stat
  "Addresses the cells that display particular statistic
  information."
  [data-source-type id meaning]
  (operations/StatisticParameter. data-source-type id meaning))

;; ## Operations ##
(defn set-value!
  "Sets the values for the given statistic table region."
  [data value]
  (operations/set-value! data value)
  (dom/set-text! (css/sel (operations/select-in-dom data))
                 value))


;;; ## Initialization ##
(defn initialize! []
  (generate-html!)
  (attach-event-listeners!)
  nil)



