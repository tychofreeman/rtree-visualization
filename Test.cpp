//
// Test.cpp
//
// This is a direct port of the C version of the RTree test program.
//

#include <stdio.h>
#include "RTree.h"

struct Rect
{
  Rect()  {}

  Rect(int a_minX, int a_minY, int a_maxX, int a_maxY)
  {
    min[0] = a_minX;
    min[1] = a_minY;

    max[0] = a_maxX;
    max[1] = a_maxY;
  }


  int min[2];
  int max[2];
};

struct Rect rects[] = 
{
  Rect(0, 0, 2, 2), // xmin, ymin, xmax, ymax (for 2 dimensional RTree)
  Rect(5, 5, 7, 7),
  Rect(8, 5, 9, 6),
  Rect(7, 1, 9, 2),
};

//int nrects = sizeof(rects) / sizeof(rects[0]);

Rect search_rect(6, 4, 10, 6); // search will find above rects that this one overlaps


bool MySearchCallback(int id, void* arg) 
{
  printf("Hit data rect %d\n", id);
  return true; // keep going
}


int main()
{
  RTree<int, int, 2, float, 4, 2> tree;

	std::cout << "(defn print-keys)" << std::endl
						<< "(defn print-keys2 [k d]" << std::endl
						<< "  (let [my-keys [k] " << std::endl
						<< "			  child-data [d]]" << std::endl
						<< "    (concat my-keys (mapcat print-keys child-data))))" << std::endl
						<< "(defn print-keys [d]" << std::endl
						<< "	(mapcat #(print-keys2 % (d %)) (keys d)))" << std::endl
						<< "" << std::endl
						<< "(defn print-links)" << std::endl
						<< "(defn print-links2 [k v]" << std::endl
						<< "  (let [child-links (map #(hash-map :source k :target %) (keys v))" << std::endl
						<< "				child-data [v]]" << std::endl
						<< "    (concat child-links (mapcat print-links child-data))))" << std::endl
						<< "(defn print-links [d]" << std::endl
						<< "	(mapcat #(print-links2 % (d %)) (keys d)))" << std::endl
						<< "" << std::endl
						<< "(defn map-conns [nodes conns]" << std::endl
						<< "	(map #(hash-map :sid (:source %) :tid (:target %) :source (.indexOf nodes (:source %)) :target (.indexOf nodes (:target %))) conns)" << std::endl
						<< ")" << std::endl
			 ;

  int i, nhits;
  int nrects = 100;

  for(i=0; i<nrects; i++)
  {
    tree.Insert(rects[2].min, rects[2].max, i);
  }
  tree.Save("Rtree.save");

  std::cout << "(print \"" << std::endl
					  << "<html>" << std::endl
  					<< "				<head>" << std::endl
  					<< "								<title>Force-Directed Layout</title>" << std::endl
  					<< "								<script type='text/javascript' src='protovis.js'></script>" << std::endl
  					<< "								<style type='text/css'>" << std::endl
  					<< "" << std::endl
  					<< "												body {" << std::endl
  					<< "																margin: 0;" << std::endl
  					<< "												}" << std::endl
  					<< "" << std::endl
  					<< "								</style>" << std::endl
  					<< "				</head>" << std::endl
  					<< "				<body>" << std::endl
  					<< "								<script type='text/javascript+protovis'>" << std::endl
						<< "\")" << std::endl
  			  	<< "(print \"var treeNodes={nodes:[\")" << std::endl
				  	<< "(print (apply str (map #(str \"{nodeName:\" % \", group:\" % \"},\n\") (print-keys2 [\"root\"] data))))" << std::endl
				  	<< "(print \"], links:[\")" << std::endl
				  	<< "(print (apply str (map #(str \"{source:\" (:source %) \", target:\" (:target %) \", value:1},\n\") (map-conns (print-keys2 [\"root\"] data) (print-links2 [\"root\"] data)))))" << std::endl
				  	<< "(print \"]};\")" << std::endl
						<< "(print \"" << std::endl
				  	<< "												var w = document.body.clientWidth," << std::endl
				  	<< "												h = document.body.clientHeight," << std::endl
				  	<< "												colors = pv.Colors.category19();" << std::endl
				  	<< "" << std::endl
				  	<< "				var vis = new pv.Panel()" << std::endl
				  	<< "				.width(w)" << std::endl
				  	<< "				.height(h)" << std::endl
				  	<< "				.fillStyle('white')" << std::endl
				  	<< "				.event('mousedown', pv.Behavior.pan())" << std::endl
				  	<< "				.event('mousewheel', pv.Behavior.zoom());" << std::endl
				  	<< "" << std::endl
				  	<< "				var force = vis.add(pv.Layout.Force)" << std::endl
				  	<< "				.nodes(treeNodes.nodes)" << std::endl
				  	<< "				.links(treeNodes.links);" << std::endl
				  	<< "" << std::endl
				  	<< "				force.link.add(pv.Line);" << std::endl
				  	<< "" << std::endl
				  	<< "				force.node.add(pv.Dot)" << std::endl
				  	<< "				.size(function(d) (d.linkDegree + 4) * Math.pow(this.scale, -1.5))" << std::endl
				  	<< "				.fillStyle(function(d) d.fix ? 'brown' : colors(d.group))" << std::endl
				  	<< "				.strokeStyle(function() this.fillStyle().darker())" << std::endl
				  	<< "				.lineWidth(1)" << std::endl
				  	<< "				.title(function(d) d.nodeName)" << std::endl
				  	<< "				.event('mousedown', pv.Behavior.drag())" << std::endl
				  	<< "				.event('drag', force);" << std::endl
				  	<< "" << std::endl
				  	<< "				vis.render();" << std::endl
				  	<< "" << std::endl
				  	<< "								</script>" << std::endl
				  	<< "				</body>" << std::endl
				  	<< "</html>" << std::endl
						<< "\")" << std::endl
					;
}
