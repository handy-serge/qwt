(ns applet.core
  (:import (java.awt Graphics Color Font RenderingHints)
           (javax.swing JApplet JButton))
  (:gen-class
     :extends javax.swing.JApplet))

(defn -paint [#^JApplet applet #^Graphics g]  ;type hint avoids Reflection, then it works without signing
  (let [width (.getWidth applet)
        height (.getHeight applet)]
    (doto g
      (.setColor (. Color YELLOW))
      (.fillRect 0 0 width height)
      (.setColor (. Color BLACK))
      (.drawRect 0 0 (dec width) (dec height))
      (.setFont (Font. "Serif" (. Font PLAIN) 24))
      (.drawString "Hello World!" 20 40))))

#_ (
(ns applet.core
  (:require [seesaw.applet :refer [defapplet]]
            [seesaw.core :refer :all]))


(defn make-content [applet]
  (border-panel
    :north "This is a Seesaw applet"
    :center (canvas :id :canvas :background "#550000")
    :south "This is a Seesaw applet"))


(defapplet
  :init #(println "popo")
  :content make-content)
)
