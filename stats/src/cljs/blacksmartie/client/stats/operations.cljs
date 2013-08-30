(ns blacksmartie.client.stats.operations
  "What can be done with the statistic data")

;; I would prefer to separate definition of abstract protocols from
;; concrete implementation. Unfortunately, I can problems to access
;; protocols defined in a separate namespace. In theory it should
;; work, in practice I had compiler warnings that symbols are not in
;; namespace.

(def state
  "Keeps track of the current value of statistical parameters"
  (atom {}))


(defprotocol DataAccess
  (set-value! [data value]
    (swap!  state assoc data value))
  (get-value [data]
    (get  @state data))
  (select-in-dom [data]))

(extend-protocol DataAccess
  nil
  (set-value! [data value])
  (get-value [data])
  (select-in-dom [data]))

(extend-protocol DataAccess
  string
  (set-value! [data value])
  (get-value [data])
  (select-in-dom [data] data))


;; ## Keep information about the type of the data source. ##
;;
;; Parameters:
;;
;; - `data-source-type` One of #{:plot :gate}
;; - `id` Id of the data source
(defrecord DataSourceType
    [data-source-type id])

(extend-protocol DataAccess
  DataSourceType
  (set-value! [data value]
    (swap! state assoc  data value))
  (get-value [data]
    (get @state data))

  (select-in-dom [data]
    (let [{:keys [data-source-type id]} data]
      (str "table.statistics"
           (format " tr[data-%s-id=\"%s\"]"
                   (name data-source-type)
                   id)
           (format " td[data-meaning=\"%s-type\"]"
                   (name data-source-type))))))

;; ## Keep channel labels ##
;; Allows to display channel labels for the given axis
;; Parameters:
;;
;; - `plot-id` One of [1 2 3 4 ...]
;; - `axis`  One of #{:x :y}
(defrecord ChannelLabel [plot-id axis])

(extend-protocol DataAccess
  ChannelLabel
  (set-value! [data value]
    (swap! state assoc  data value))
  (get-value [data]
    (get @state data))
  (select-in-dom [data]
    (let [{:keys [plot-id axis]} data]
      (str "table.statistics"
       (format " tr.plot-header[data-plot-id=\"%s\"]"
               plot-id)
       (format " td[data-axis=\"%s\"]"
               (name axis))))))

;; ## Two-dimensional statistics parameter ##
(defrecord StatisticParameter2D
    [data-source-type
     id
     meaning
     axis])

(extend-protocol DataAccess
  StatisticParameter2D
  (set-value! [data value]
    (swap! state assoc  data value))

  (get-value [data]
    (get @state data))

  (select-in-dom [data]
    (let [{:keys [data-source-type id meaning axis]} data]
      (str "table.statistics"
           (format " tr[data-%s-id=\"%s\"]"
                   (name data-source-type)
                   id)
           (format " td[data-meaning=\"%s\"][data-axis=\"%s\"]"
                   (name meaning)
                   (name axis))))))

;; ## Single-dimensional statistic parameter  ##
(defrecord StatisticParameter
    [data-source-type
     id
     meaning])

(extend-protocol DataAccess
  StatisticParameter
  (set-value! [data value]
    (swap! state assoc  data value))

  (get-value [data]
    (get @state data))

  (select-in-dom [data]
    (let [{:keys [data-source-type id meaning]} data]
      (str "table.statistics"
           (format " tr[data-%s-id=\"%s\"]"
                   (name data-source-type)
                   id)
           (format " td[data-meaning=\"%s\"]"
                   (name meaning))))))
