function trace( str ){
	fl.outputPanel.trace( str );
}

//创建地图片段
function createMapTiles(){
	var doc = fl.getDocumentDOM()
	var lib = doc.library; //library 对象
	var libLength = lib.items.length;
	var itemArr = [];

	for(var i=0; i < libLength; i++) {
	   //将位图放入数组
	   if(lib.items[i].itemType=="bitmap" && ((lib.items[i].name).indexOf("/")==-1))
	   itemArr.push(lib.items[i]);
	}
	
	var itemLen = itemArr.length
	for (var i = 0; i < itemLen; i++) {

		var itemIndex = doc.library.findItemIndex("cell_m_"+i);
		if (itemIndex != ""){
			continue;
		}

	   var itemName = itemArr[i].name;

	   var expName = itemName.split(".")[0]; //不带后缀名
	   lib.selectItem(itemName); //选中位图
	   lib.addItemToDocument({x:0,y:0});
	   doc.selectAll();
	   //doc.scaleSelection(0.5,0.5);
	   
	   doc.convertToSymbol("movie clip","img_"+expName,"center") ; //将位图转化为mc元件
	   doc.convertToSymbol("movie clip", "cell_"+expName, "bottom left");

	   //if (lib.getItemProperty('linkageImportForRS') == true) {
	   //     lib.setItemProperty('linkageImportForRS', false);
	   //}
	   //lib.setItemProperty('linkageExportForAS', true);
	   //lib.setItemProperty('linkageExportForRS', false);
	   //lib.setItemProperty('linkageExportInFirstFrame', true);
	   //lib.setItemProperty('linkageClassName', "img_"+expName);
	   //lib.setItemProperty('scalingGrid',  false);//是否现实9公格参考线
	   doc.selectAll(); //清空舞台
	   doc.deleteSelection();
	}
}

function placeMapTiles(){
	
	var doc = fl.getDocumentDOM()
	var col = 5;
	var row = 5;
	var idx = 0

	for(var i = 0; i < row; i++)
	{
		for(var j = 0; j < col; j++)
		{
			var itemIndex = doc.library.findItemIndex("cell_m_"+idx);
			if (itemIndex != ""){
				var theItem = doc.library.items[itemIndex];
				doc.addItem({x:j*40,y:i*40}, theItem);
				idx++;
			}
		}
	}
}

//对片段地图命名
function renameMapTiles(){

	var nlayer = doc.getTimeline().layerCount
	var layers = doc.getTimeline().layers
	for( var layer_index = nlayer-1; layer_index >= 0; --layer_index ){

		var layer = layers[layer_index];	
		var nframe = layer.frameCount;

		for( var frame_index = 0; frame_index < nframe; ++frame_index ){

			var frame = layer.frames[frame_index]
			var nelement = frame.elements.length;

			for( var element_index = 0; element_index < nelement; ++element_index ){
				
				var element = frame.elements[element_index];
				if (element.libraryItem.name.indexOf("cell_") != -1){ //包含cell
					element.name = element.libraryItem.name
					var child = element.libraryItem.timeline.layers[0].frames[0].elements[0]
					child.name = child.libraryItem.name
				}
			}
		}
	}
}

function main(){
	createMapTiles()
	placeMapTiles()
	renameMapTiles()
}

main()