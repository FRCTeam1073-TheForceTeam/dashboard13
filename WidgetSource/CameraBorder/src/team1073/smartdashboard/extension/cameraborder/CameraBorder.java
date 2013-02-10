package team1073.smartdashboard.extension.cameraborder;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.properties.BooleanProperty;
import edu.wpi.first.smartdashboard.types.DataType;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Canvas;
import javax.swing.JFrame;

public class CameraBorder extends StaticWidget{
    private boolean isOldImage;
    public final BooleanProperty newVal = new BooleanProperty(this, "Is Old Image", false);
    public static final DataType[] TYPES = {DataType.BOOLEAN};
    
    public CameraBorder () {isOldImage = false;}
    
    @Override
    protected void paintComponent (Graphics graphics) {
        
        if(!isOldImage) {graphics.setColor(Color.BLACK);}
        else {graphics.setColor(Color.RED);}
        
        graphics.fillRect(10, 10, 680, 520);
    }

    public void setValue(Object o) {
       boolean b = isOldImage;
       
       try{b = (Boolean) o;}
       catch(Exception e){}
       
       isOldImage = b;
       repaint();
    }

    @Override
    public void init() {
       isOldImage = false;
       setPreferredSize(new Dimension(50,50));
    }

    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }  
}
