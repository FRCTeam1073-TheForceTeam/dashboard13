package team1073.smartdashboard.extension.disccount;

//import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.properties.IntegerProperty;
import edu.wpi.first.smartdashboard.types.DataType;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Canvas;
import javax.swing.JFrame;
import edu.wpi.first.smartdashboard.gui.StaticWidget;

public class DiscCount extends StaticWidget{
    
    private int count;
    public final IntegerProperty newVal = new IntegerProperty(this, "Disc Number", 0);
    public static final DataType[] TYPES = {DataType.NUMBER};
    
    public DiscCount () { count = 0;}
    
    @Override
    protected void paintComponent (Graphics graphics) {
        graphics.setColor (Color.BLACK);
        graphics.fillRect(60,80,330,100);

        for (int i = 0; i < count; i++) 
        {
            if(count == 4) 
                graphics.setColor(Color.RED);
            else
                graphics.setColor(Color.WHITE);
            graphics.fillOval(i*80+70, 95, 70, 70);
        }
        graphics.setColor(Color.BLACK);
        //graphics.drawString("Team 1073 Disc Counter", 160, 50);
    }
    
    public void setValue(Object o) {
        int i = count;
        
        try{i = ((Number)o).intValue();}
        catch(Exception e) {}
        
        count = i >= 0 && i <= 4 ? i : count;
        repaint();
    }
    
    @Override
    public void init() {
        count = 0;
        setPreferredSize(new Dimension(330, 100));
    }
    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }  
}