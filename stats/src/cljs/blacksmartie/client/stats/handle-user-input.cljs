(ns blacksmartie.client.stats.handle-user-input
  "Defines what happens when user click on stats display controls."
    (:require-macros [blacksmartie.client.cytoapp :refer [when-cytoapp-as]])
    (:require   [domina.events :as events]
                [domina :as dom]
                [blacksmartie.client.stats.generate-csv :refer [generate-csv]]))

(defn save-statistics-as-csv []
  (let [csv (generate-csv)]
    (.log js/console "cytoapp.saveStatisticsAsCsv: START")
    (.log js/console csv)
    (when-cytoapp-as [app]
                     (.saveStatisticsAsCsv app csv))
    (.log js/console "cytoapp.saveStatisticsAsCsv: FINISH")))

(defn attach-event-listeners! []
  (when (and js/document
           (.-getElementById js/document))
    (events/listen! (dom/by-id "save-as-csv") :click save-statistics-as-csv)))
