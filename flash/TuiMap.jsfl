function trace( str ){
	fl.outputPanel.trace( str );
}

//创建地图块
function createMapTiles(row,col,cellWidth,cellHeight,fixName){
	var doc = fl.getDocumentDOM()
	var lib = doc.library; //library 对象

	var idx = 0
	for(var i = 0; i < row; i++)
	{
		for(var j = 0; j < col; j++)
		{		
			var imgName = "img_"+fixName+i+"_"+j;
			if (lib.findItemIndex(imgName) != ""){
				continue;
			}

			lib.selectNone()
			lib.duplicateItem("img_tpl")
			lib.renameItem(imgName)
			lib.editItem(imgName)
			lib.addItemToDocument({x:cellWidth/2,y:cellHeight/2},imgName+".png")

			var cellName = "cell_"+fixName+idx
			if (lib.findItemIndex(cellName) != ""){
				continue;
			}
			
			lib.selectNone()
			lib.addNewItem("movie clip",cellName)
			idx++;
			lib.editItem(cellName)
			lib.addItemToDocument({x:0,y:0},imgName)

			doc.exitEditMode()
			lib.addItemToDocument({x:j*cellWidth,y:i*cellHeight},cellName)
		}
	}
}

//对片段地图命名
function renameMapTiles(){
	var doc = fl.getDocumentDOM()
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
	
	var col = 16;
	var row = 16;
	var cellWidth = 64;
	var cellHeight = 64;
	var fixName = "m_"

	createMapTiles(row,col,cellWidth,cellHeight,fixName)
	renameMapTiles()
}

main()