using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Globalization;
using System.Collections;
using System.Diagnostics;
using System.Reflection;
using System.Threading;
using System.Resources;

namespace WindowsFormsApplication1
{

    public partial class Form1 : Form
    {
        static CultureInfo m_cultureInfo;
        private void ChangeFormLanguage(Form form, string newLanguageString)
        {
            form.SuspendLayout();
            Cursor.Current = Cursors.WaitCursor;
            ResourceManager resources = new ResourceManager(form.GetType());
            m_cultureInfo = new CultureInfo(newLanguageString);
            // change main form resources
            form.Text = resources.GetString("$this.Text", m_cultureInfo);
            ReloadControlCommonProperties(form, resources);
            ToolTip toolTip = GetToolTip(form);
            // change text of all containing controls
            RecurControls(form, resources, toolTip);
            // change the text of menus
            ScanNonControls(form, resources);
            form.ResumeLayout();
        }

        public object GetSafeValue(System.Resources.ResourceManager resources, string name, object currentValue)
        {
            object newValue = resources.GetObject(name, m_cultureInfo);
            if (newValue == null)
            {
                Trace.WriteLine(string.Format("Resource for {0} not found, using current value.", name));
                return currentValue;
            }
            return newValue;
        }

        public virtual void ScanNonControls(System.Windows.Forms.ContainerControl containerControl, System.Resources.ResourceManager resources)
        {
            FieldInfo[] fieldInfo = containerControl.GetType().GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);
            for (int i = 0; i < fieldInfo.Length; i++)
            {
                object obj = fieldInfo[i].GetValue(containerControl);
                string fieldName = fieldInfo[i].Name;
                if (obj is System.Windows.Forms.MenuItem)
                {
                    System.Windows.Forms.MenuItem menuItem = (System.Windows.Forms.MenuItem)obj;
                    menuItem.Enabled = (bool)(GetSafeValue(resources, fieldName + ".Enabled", menuItem.Enabled));
                    menuItem.Shortcut = (System.Windows.Forms.Shortcut)(GetSafeValue(resources, fieldName + ".Shortcut", menuItem.Shortcut));
                    menuItem.ShowShortcut = (bool)(GetSafeValue(resources, fieldName + ".ShowShortcut", menuItem.ShowShortcut));
                    menuItem.Text = (string)GetSafeValue(resources, fieldName + ".Text", menuItem.Text);
                    menuItem.Visible = (bool)(GetSafeValue(resources, fieldName + ".Visible", menuItem.Visible));
                }
                if (obj is System.Windows.Forms.StatusBarPanel)
                {
                    System.Windows.Forms.StatusBarPanel panel = (System.Windows.Forms.StatusBarPanel)obj;
                    panel.Alignment = (System.Windows.Forms.HorizontalAlignment)(GetSafeValue(resources, fieldName + ".Alignment", panel.Alignment));
                    panel.Icon = (System.Drawing.Icon)(GetSafeValue(resources, fieldName + ".Icon", panel.Icon));
                    panel.MinWidth = (int)(GetSafeValue(resources, fieldName + ".MinWidth", panel.MinWidth));
                    panel.Text = (string)(GetSafeValue(resources, fieldName + ".Text", panel.Text));
                    panel.ToolTipText = (string)(GetSafeValue(resources, fieldName + ".ToolTipText", panel.ToolTipText));
                    panel.Width = (int)(GetSafeValue(resources, fieldName + ".Width", panel.Width));
                }
                if (obj is System.Windows.Forms.ColumnHeader)
                {
                    System.Windows.Forms.ColumnHeader header = (System.Windows.Forms.ColumnHeader)obj;
                    header.Text = (string)(GetSafeValue(resources, fieldName + ".Text", header.Text));
                    header.TextAlign = (System.Windows.Forms.HorizontalAlignment)(GetSafeValue(resources, fieldName + ".TextAlign", header.TextAlign));
                    header.Width = (int)(GetSafeValue(resources, fieldName + ".Width", header.Width));
                }
                if (obj is System.Windows.Forms.ToolBarButton)
                {
                    System.Windows.Forms.ToolBarButton button = (System.Windows.Forms.ToolBarButton)obj;
                    button.Enabled = (bool)(GetSafeValue(resources, fieldName + ".Enabled", button.Enabled));
                    button.ImageIndex = (int)(GetSafeValue(resources, fieldName + ".ImageIndex", button.ImageIndex));
                    button.Text = (string)(GetSafeValue(resources, fieldName + ".Text", button.Text));
                    button.ToolTipText = (string)(GetSafeValue(resources, fieldName + ".ToolTipText", button.ToolTipText));
                    button.Visible = (bool)(GetSafeValue(resources, fieldName + ".Visible", button.Visible));
                }
            }
        }

        protected virtual void ReloadControlCommonProperties(Control control,
                                         ResourceManager resources)
        {
            SetProperty(control, "AccessibleDescription", resources);
            SetProperty(control, "AccessibleName", resources);
            SetProperty(control, "BackgroundImage", resources);
            SetProperty(control, "Font", resources);
            SetProperty(control, "ImeMode", resources);
            SetProperty(control, "RightToLeft", resources);
            SetProperty(control, "Size", resources);
            // following properties are not changed for the form
            if (!(control is System.Windows.Forms.Form))
            {
                SetProperty(control, "Anchor", resources);
                SetProperty(control, "Dock", resources);
                SetProperty(control, "Enabled", resources);
                SetProperty(control, "Location", resources);
                SetProperty(control, "TabIndex", resources);
                SetProperty(control, "Visible", resources);
            }
            if (control is ScrollableControl)
            {
                // reloads properties specific to ScrollableControl:
                // AutoScroll, AutoScrollMargin, AutoScrollMinSize
                ReloadScrollableControlProperties((ScrollableControl)control, resources);
                if (control is Form)
                {
                    // reloads properties specific to Form control only:
                    // AutoScaleBaseSize, Icon, MaximumSize and MinimumSize
                    ReloadFormProperties((Form)control, resources);
                }
            }
        }

        private void ReloadScrollableControlProperties(System.Windows.Forms.ScrollableControl control, System.Resources.ResourceManager resources)
        {
            SetProperty(control, "AutoScroll", resources);
            SetProperty(control, "AutoScrollMargin", resources);
            SetProperty(control, "AutoScrollMinSize", resources);
        }

        private void ReloadFormProperties(System.Windows.Forms.Form form, System.Resources.ResourceManager resources)
        {
            SetProperty(form, "AutoScaleBaseSize", resources);
            SetProperty(form, "Icon", resources);
            SetProperty(form, "MaximumSize", resources);
            SetProperty(form, "MinimumSize", resources);
        }

        public ToolTip GetToolTip(System.Windows.Forms.Control control)
        {
            Debug.Assert(control is System.Windows.Forms.Form || control is System.Windows.Forms.UserControl);
            FieldInfo[] fieldInfo = control.GetType().GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);
            for (int i = 0; i < fieldInfo.Length; i++)
            {
                object obj = fieldInfo[i].GetValue(control);
                if (obj is System.Windows.Forms.ToolTip)
                    return (ToolTip)obj;
            }
            return null;
        }

        public virtual void ReloadTextForSelectedControls(System.Windows.Forms.Control control, System.Resources.ResourceManager resources)
        {
            if (control is System.Windows.Forms.AxHost ||
                control is System.Windows.Forms.ButtonBase ||
                control is System.Windows.Forms.GroupBox ||
                control is System.Windows.Forms.Label ||
                control is System.Windows.Forms.ScrollableControl ||
                control is System.Windows.Forms.StatusBar ||
                control is System.Windows.Forms.TabControl ||
                control is System.Windows.Forms.ToolBar)
            {
                control.Text = (string)GetSafeValue(resources, control.Name + ".Text", control.Text);
            }
        }

        private void SetProperty(Control control, string propertyName,
                               ResourceManager resources)
        {
            PropertyInfo propertyInfo = control.GetType().GetProperty(propertyName);
            if (propertyInfo != null)
            {
                string controlName = control.Name;
                if (control is Form)
                    controlName = "$this";
                object resObject = resources.GetObject(controlName + "." +
                                             propertyName, m_cultureInfo);
                if (resObject != null)
                    propertyInfo.SetValue(control, Convert.ChangeType(resObject,
                                              propertyInfo.PropertyType), null);
            }
        }


        private void RecurControls(Control parent,
                    ResourceManager resources, ToolTip toolTip)
        {
            foreach (Control control in parent.Controls)
            {
                ReloadControlCommonProperties(control, resources);
                ReloadControlSpecificProperties(control, resources);
                if (toolTip != null)
                    toolTip.SetToolTip(control, resources.GetString(control.Name +
                                                      ".ToolTip", m_cultureInfo));
                if (control is UserControl)
                    RecurUserControl((UserControl)control);
                else
                {
                    ReloadTextForSelectedControls(control, resources);
                    // change ListBox and ComboBox items
                    ReloadListItems(control, resources);
                    if (control is TreeView)
                        ReloadTreeViewNodes((TreeView)control, resources);
                    if (control.Controls.Count > 0)
                        RecurControls(control, resources, toolTip);
                }
            }
        }

        private void ReloadComboBoxItems(System.Windows.Forms.ComboBox comboBox, System.Resources.ResourceManager resources)
        {
            if (comboBox.Items.Count > 0)
            {
                int selectedIndex = comboBox.SelectedIndex;
                ReloadItems(comboBox.Name, comboBox.Items, comboBox.Items.Count, resources);
                if (!comboBox.Sorted)
                    comboBox.SelectedIndex = selectedIndex;
            }
        }

        private void ReloadItems(string controlName, IList list, int itemsNumber, System.Resources.ResourceManager resources)
        {
            string resourceName = controlName + ".Items";
            object obj = resources.GetString(resourceName, m_cultureInfo);
            // VS2002 generates item resource name with additional ".Items" string
            if (obj == null)
            {
                resourceName += ".Items";
                obj = resources.GetString(resourceName, m_cultureInfo);
            }
            if (obj != null)
            {
                list.Clear();
                Debug.Assert(obj != null);
                list.Add(obj);
                for (int i = 1; i < itemsNumber; i++)
                    list.Add(resources.GetString(resourceName + i, m_cultureInfo));
            }
        }

        private void ReloadTreeViewNodes(System.Windows.Forms.TreeView treeView, System.Resources.ResourceManager resources)
        {
            if (treeView.Nodes.Count > 0)
            {
                string resourceName = treeView.Name + ".Nodes";
                TreeNode[] newNodes = new TreeNode[treeView.Nodes.Count];
                newNodes[0] = (System.Windows.Forms.TreeNode)resources.GetObject(resourceName, m_cultureInfo);
                // VS2002 generates node resource names with additional ".Nodes" string
                if (newNodes[0] == null)
                {
                    resourceName += ".Nodes";
                    newNodes[0] = (System.Windows.Forms.TreeNode)resources.GetObject(resourceName, m_cultureInfo);
                }
                Debug.Assert(newNodes[0] != null);
                for (int i = 1; i < treeView.Nodes.Count; i++)
                {
                    newNodes[i] = (System.Windows.Forms.TreeNode)resources.GetObject(resourceName + i.ToString(), m_cultureInfo);
                }
                treeView.Nodes.Clear();
                treeView.Nodes.AddRange(newNodes);
            }
        }

        private void ReloadUpDownItems(System.Windows.Forms.DomainUpDown domainUpDown, System.Resources.ResourceManager resources)
        {
            if (domainUpDown.Items.Count > 0)
            {
                int selectedIndex = domainUpDown.SelectedIndex;
                ReloadItems(domainUpDown.Name, domainUpDown.Items, domainUpDown.Items.Count, resources);
                if (!domainUpDown.Sorted)
                    domainUpDown.SelectedIndex = selectedIndex;
            }
        }

        private void ReloadListBoxItems(System.Windows.Forms.ListBox listBox, System.Resources.ResourceManager resources)
        {
            if (listBox.Items.Count > 0)
            {
                int[] selectedItems = new int[listBox.SelectedIndices.Count];
                listBox.SelectedIndices.CopyTo(selectedItems, 0);
                ReloadItems(listBox.Name, listBox.Items, listBox.Items.Count, resources);
                if (!listBox.Sorted)
                {
                    for (int i = 0; i < selectedItems.Length; i++)
                    {
                        listBox.SetSelected(selectedItems[i], true);
                    }
                }
            }
        }

        public virtual void ReloadListItems(System.Windows.Forms.Control control, System.Resources.ResourceManager resources)
        {
            if (control is System.Windows.Forms.ComboBox)
                ReloadComboBoxItems((System.Windows.Forms.ComboBox)control, resources);
            else if (control is System.Windows.Forms.ListBox)
                ReloadListBoxItems((System.Windows.Forms.ListBox)control, resources);
            else if (control is System.Windows.Forms.DomainUpDown)
                ReloadUpDownItems((System.Windows.Forms.DomainUpDown)control, resources);
        }

        protected virtual void
         ReloadControlSpecificProperties(System.Windows.Forms.Control control,
         System.Resources.ResourceManager resources)
        {
            // ImageIndex property for ButtonBase, Label,
            // TabPage, ToolBarButton, TreeNode, TreeView
            SetProperty(control, "ImageIndex", resources);
            // ToolTipText property for StatusBar, TabPage, ToolBarButton
            SetProperty(control, "ToolTipText", resources);
            // IntegralHeight property for ComboBox, ListBox
            SetProperty(control, "IntegralHeight", resources);
            // ItemHeight property for ListBox, ComboBox, TreeView
            SetProperty(control, "ItemHeight", resources);
            // MaxDropDownItems property for ComboBox
            SetProperty(control, "MaxDropDownItems", resources);
            // MaxLength property for ComboBox, RichTextBox, TextBoxBase
            SetProperty(control, "MaxLength", resources);
            // Appearance property for CheckBox, RadioButton, TabControl, ToolBar
            SetProperty(control, "Appearance", resources);
            // CheckAlign property for CheckBox and RadioBox
            SetProperty(control, "CheckAlign", resources);
            // FlatStyle property for ButtonBase, GroupBox and Label
            SetProperty(control, "FlatStyle", resources);
            // ImageAlign property for ButtonBase, Image and Label
            SetProperty(control, "ImageAlign", resources);
            // Indent property for TreeView
            SetProperty(control, "Indent", resources);
            // Multiline property for RichTextBox, TabControl, TextBoxBase
            SetProperty(control, "Multiline", resources);
            // BulletIndent property for RichTextBox
            SetProperty(control, "BulletIndent", resources);
            // RightMargin property for RichTextBox
            SetProperty(control, "RightMargin", resources);
            // ScrollBars property for RichTextBox, TextBox
            SetProperty(control, "ScrollBars", resources);
            // WordWrap property for TextBoxBase
            SetProperty(control, "WordWrap", resources);
            // ZoomFactor property for RichTextBox
            SetProperty(control, "ZoomFactor", resources);
        }


        private void RecurUserControl(UserControl userControl)
        {
            ResourceManager resources = new ResourceManager(userControl.GetType());
            ToolTip toolTip = GetToolTip(userControl);
            RecurControls(userControl, resources, toolTip);
        }


        protected virtual void ScanNonControls(Form form, ResourceManager resources)
        {
            FieldInfo[] fieldInfo = form.GetType().GetFields(BindingFlags.NonPublic
                                    | BindingFlags.Instance | BindingFlags.Public);
            for (int i = 0; i < fieldInfo.Length; i++)
            {
                object obj = fieldInfo[i].GetValue(form);
                string fieldName = fieldInfo[i].Name;
                if (obj is MenuItem)
                {
                    MenuItem menuItem = (MenuItem)obj;
                    menuItem.Enabled = (bool)(resources.GetObject(fieldName +
                                                 ".Enabled", m_cultureInfo));
                    // etc.
                }
                if (obj is StatusBarPanel)
                {
                    StatusBarPanel panel = (StatusBarPanel)obj;
                    panel.Alignment =
                      (HorizontalAlignment)(resources.GetObject(fieldName +
                      ".Alignment", m_cultureInfo));
                }
                if (obj is ColumnHeader)
                {
                    ColumnHeader header = (ColumnHeader)obj;
                    header.Text = resources.GetString(fieldName + ".Text", m_cultureInfo);
                    header.TextAlign =
                      (HorizontalAlignment)(resources.GetObject(fieldName +
                      ".TextAlign", m_cultureInfo));
                    header.Width = (int)(resources.GetObject(fieldName + ".Width", m_cultureInfo));
                }
                if (obj is ToolBarButton)
                {
                    ToolBarButton button = (ToolBarButton)obj;
                    button.Enabled = (bool)(resources.GetObject(fieldName +
                                               ".Enabled", m_cultureInfo));
                }
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void groupBox3_Enter(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            ChangeFormLanguage(this, "en-US");
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            ChangeFormLanguage(this, "ru-RU");
        }
    }
}
