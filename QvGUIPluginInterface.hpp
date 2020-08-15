#pragma once
#include "QvPluginBase.hpp"

#include <QMenu>
#include <QWidget>

namespace Qv2rayPlugin
{
    class QvPluginSettingsWidget : public QWidget
    {
        Q_OBJECT
      public:
        explicit QvPluginSettingsWidget(QWidget *parent) : QWidget(parent){};
        virtual ~QvPluginSettingsWidget(){};
        virtual void SetSettings(const QJsonObject &) = 0;
        virtual QJsonObject GetSettings() = 0;
    };

    class QvPluginMainWindowWidget : public QWidget
    {
        Q_OBJECT
      public:
        explicit QvPluginMainWindowWidget(QWidget *parent) : QWidget(parent){};
        virtual ~QvPluginMainWindowWidget(){};
        virtual const QList<QMenu *> GetMenus() = 0;
    };

    class QvPluginEditor : public QWidget
    {
        Q_OBJECT
      public:
        explicit QvPluginEditor(QWidget *parent = nullptr) : QWidget(parent){};
        virtual ~QvPluginEditor(){};
        //
        virtual void SetHostAddress(const QString &address, int port) = 0;
        virtual QPair<QString, int> GetHostAddress() const = 0;
        //
        virtual void SetContent(const QJsonObject &) = 0;
        virtual const QJsonObject GetContent() const = 0;

      protected:
        QJsonObject content;
    };

    template<typename T>
    inline QPair<ProtocolInfoObject, T *> MakeEditorInfoPair(const QString &protocol, const QString &displayName)
    {
        return { ProtocolInfoObject(protocol, displayName), new T() };
    }

    class PluginGUIInterface
    {
      public:
        using typed_plugin_editor = QPair<ProtocolInfoObject, QvPluginEditor *>;
        explicit PluginGUIInterface(){};
        virtual ~PluginGUIInterface(){};
        virtual QIcon Icon() const = 0;
        virtual QList<PluginGuiComponentType> GetComponents() const = 0;
        virtual std::unique_ptr<QvPluginSettingsWidget> GetSettingsWidget() const final
        {
            return createSettingsWidgets();
        }
        virtual QList<typed_plugin_editor> GetInboundEditors() const final
        {
            return createInboundEditors();
        }
        virtual QList<typed_plugin_editor> GetOutboundEditors() const final
        {
            return createOutboundEditors();
        }
        virtual std::unique_ptr<QvPluginMainWindowWidget> GetMainWindowWidget() const final
        {
            return createMainWindowWidget();
        }

      protected:
        virtual std::unique_ptr<QvPluginSettingsWidget> createSettingsWidgets() const = 0;
        virtual QList<typed_plugin_editor> createInboundEditors() const = 0;
        virtual QList<typed_plugin_editor> createOutboundEditors() const = 0;
        virtual std::unique_ptr<QvPluginMainWindowWidget> createMainWindowWidget() const = 0;
    };

} // namespace Qv2rayPlugin
