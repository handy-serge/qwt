(ns stats.cytoapp)


(defmacro when-cytoapp-as [[object] & body]
  `(let [~object (.-cytoapp js/window)]
     (when (not= js/undefined ~object)
       ~@body)))

(defmacro if-cytoapp-as [[object] then-form & [else-form]]
  `(let [~object (.-cytoapp js/window)]
     (if (not= js/undefined ~object)
       ~then-form
       ~else-form)))