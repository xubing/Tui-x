var lib = fl.getDocumentDOM().library; //library 对象
var libLength = lib.items.length;
var itemArr = [];
for(var i=0; i < libLength; i++) {
   //将位图放入数组
   if(lib.items[i].itemType=="bitmap" && ((lib.items[i].name).indexOf("/")==-1))
   itemArr.push(lib.items[i]);
}
for (var i = 0; i < itemArr.length; i++) {
   var itemName = itemArr[i].name;
   var expName = itemName.split(".")[0]; //不带后缀名
   lib.selectItem(itemName); //选中位图
   lib.addItemToDocument({x:0,y:0});
   fl.getDocumentDOM().selectAll();
   //fl.getDocumentDOM().scaleSelection(0.5,0.5);
   fl.getDocumentDOM().convertToSymbol("movie clip","img_"+expName,"bottom left") ; //将位图转化为mc元件
	/*   
   if (lib.getItemProperty('linkageImportForRS') == true) {
        lib.setItemProperty('linkageImportForRS', false);
   }
   lib.setItemProperty('linkageExportForAS', true);
   lib.setItemProperty('linkageExportForRS', false);
   lib.setItemProperty('linkageExportInFirstFrame', true);
   lib.setItemProperty('linkageClassName', "img_"+expName);
   */
   lib.setItemProperty('scalingGrid',  false);//是否现实9公格参考线
   fl.getDocumentDOM().selectAll(); //清空舞台
   fl.getDocumentDOM().deleteSelection();
}